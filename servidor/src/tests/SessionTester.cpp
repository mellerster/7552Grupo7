#include <string>

#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "rocaDB/IDB.hpp"
#include "posicionaitor/IPosicionador.hpp"
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


