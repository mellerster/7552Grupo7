#include <string>

#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "rocaDB/IDB.hpp"
#include "helpers/IPosicionador.hpp"
#include "DataService.hpp"



TEST_CASE ( "Testear manejor de session" ) {
    // Mocks
    MockRepository mocker;
    IDB* mockedDB = mocker.Mock<IDB>();
    IPosicionador* mockedPositionator = mocker.Mock<IPosicionador>();

    mocker.OnCall( mockedDB, IDB::Open );
    mocker.OnCall( mockedDB, IDB::Close );

    // Se instancia el "SUT"
    DataService ds( *mockedDB, *mockedPositionator );

    SECTION ( "Token no activo" ) {
        unsigned int tok = 123456;

        bool active = ds.IsTokenActive(tok);

        REQUIRE_FALSE( active );
    }

    SECTION ( "Iniciar session" ) {
        mocker.ExpectCall( mockedDB, IDB::AutheticateUser).Return( true );

        unsigned int tok = ds.StartSession( "pepe", "1234" );

        REQUIRE ( tok != 0 );
    }

    SECTION ( "Iniciar session falla" ) {
        mocker.ExpectCall( mockedDB, IDB::AutheticateUser).Return( false );

        unsigned int tok = ds.StartSession( "pepe", "1234" );

        REQUIRE ( tok == 0 );
    }

    SECTION ( "Token activo" ) {
        mocker.ExpectCall( mockedDB, IDB::AutheticateUser).Return( true );

        unsigned int tok = ds.StartSession( "pepe", "1234" );
        bool active = ds.IsTokenActive( tok );

        REQUIRE ( active );
    }

    SECTION ( "Los token son unicos" ) {
        mocker.ExpectCall( mockedDB, IDB::AutheticateUser).Return( true );
        mocker.ExpectCall( mockedDB, IDB::AutheticateUser).Return( true );

        unsigned int tok1 = ds.StartSession( "pepe", "1234" );
        unsigned int tok2 = ds.StartSession( "pepa", "4321" );

        REQUIRE ( tok1 != tok2 );
    }

    SECTION ( "Renovar sesion" ) {
        mocker.OnCall( mockedDB, IDB::AutheticateUser).Return( true );

        unsigned int oldToken = ds.StartSession( "pepe", "1234" );
        unsigned int newToken = ds.StartSession( "pepe", "1234" );

        // Renovar la sesion genera un token nuevo
        REQUIRE ( 0 != oldToken );
        REQUIRE ( 0 != newToken );
        REQUIRE ( newToken != oldToken );
    }

    SECTION ( "Terminar sesion" ) {
        mocker.OnCall( mockedDB, IDB::AutheticateUser).Return( true );

        unsigned int tok = ds.StartSession( "pepe", "1234" );
        bool existeSesionInicial = ds.IsTokenActive( tok );

        // Act
        ds.EndSession( tok );
        bool existeSesionFinal = ds.IsTokenActive( tok );

        // Assert
        REQUIRE ( 0 != tok );
        REQUIRE ( existeSesionInicial );
        REQUIRE_FALSE ( existeSesionFinal );
    }

}


TEST_CASE ( "Registrar nuevos usuarios" ) {
    // Mocks
    MockRepository mocker;
    IDB* mockedDB = mocker.Mock<IDB>();
    IPosicionador* mockedPositionator = mocker.Mock<IPosicionador>();

    mocker.OnCall( mockedDB, IDB::Open );
    mocker.OnCall( mockedDB, IDB::Close );

    // Se instancia el "SUT"
    DataService ds( *mockedDB, *mockedPositionator );

    SECTION ( "Nuevo usuario" ) {
        mocker.ExpectCall( mockedDB, IDB::ExistsUser).Return( false );
        mocker.ExpectCall( mockedDB, IDB::CreateUser).Return( true );

        bool exito = ds.RegisterNewUser( "pepe", "1234" );

        REQUIRE ( exito );
    }

    SECTION ( "Trata de crear un usuario existente" ) {
        mocker.ExpectCall( mockedDB, IDB::ExistsUser).Return( true );

        bool exito = ds.RegisterNewUser( "pepe", "1234" );

        REQUIRE_FALSE ( exito );
    }

}


TEST_CASE ( "Manejar estados de usuarios" ) {
    // Mocks
    MockRepository mocker;
    IDB* mockedDB = mocker.Mock<IDB>();
    IPosicionador* mockedPositionator = mocker.Mock<IPosicionador>();

    mocker.OnCall( mockedDB, IDB::Open );
    mocker.OnCall( mockedDB, IDB::Close );
    mocker.OnCall( mockedDB, IDB::ExistsUser ).Return( true );
    mocker.OnCall( mockedDB, IDB::AutheticateUser ).Return( true );

    mocker.OnCall( mockedDB, IDB::LoadUserFoto ).With( _, Out(":-)") ).Return( true );
    mocker.OnCall( mockedDB, IDB::LoadUserUbicacion ).With( _, Out("1"), Out("2") ).Return( true );

    mocker.OnCall( mockedPositionator, IPosicionador::getLugarMasCercano ).Return( "Kyoto" );

    // Se instancia el servicio
    DataService ds( *mockedDB, *mockedPositionator );

    unsigned int token = ds.StartSession( "pepe", "1234" );

    SECTION ( "iniciar conectado" ) {
        UserProfile prof = ds.GetUserProfile( token, "pepe" );

        REQUIRE ( "C" == prof.Estado );
    }

    SECTION ( "No estar conectado" ) {
        UserProfile prof = ds.GetUserProfile( token, "pepito" );

        REQUIRE ( "D" == prof.Estado );
    }

    SECTION ( "Desconectarse" ) {
        // "Pepito" obtiene el estado de "pepe"
        unsigned int tokenito = ds.StartSession( "pepito", "1234" );
        UserProfile profConn = ds.GetUserProfile( tokenito, "pepe" );

        // Se desloggea "pepe" y "pepito" pide su estado
        ds.EndSession( token );
        UserProfile profDesc = ds.GetUserProfile( tokenito, "pepe" );

        REQUIRE ( "C" == profConn.Estado );
        REQUIRE ( "D" == profDesc.Estado );
    }


    SECTION ( "Cambiar estado: Conectado" ) {
        // Act
        ds.ChangeEstado( token, "C" );
        UserProfile prof = ds.GetUserProfile( token, "pepe" );

        // Assert
        REQUIRE ( "C" == prof.Estado );
    }

    SECTION ( "Cambiar estado: Des-conectado" ) {
        // Act
        ds.ChangeEstado( token, "D" );
        UserProfile prof = ds.GetUserProfile( token, "pepe" );

        // Assert
        REQUIRE ( "D" == prof.Estado );
    }

    SECTION ( "Cambiar estado: Estado invalido de un usuario conectado" ) {
        // Act
        ds.ChangeEstado( token, "goool!" );
        UserProfile prof = ds.GetUserProfile( token, "pepe" );

        // Assert
        REQUIRE ( "C" == prof.Estado );
    }

    SECTION ( "Cambiar estado: Estado invalido de un usuario desconectado" ) {
        // Act
        ds.ChangeEstado( token, "goool!" );
        UserProfile prof = ds.GetUserProfile( token, "pepito" );

        // Assert
        REQUIRE ( "D" == prof.Estado );
    }
}


