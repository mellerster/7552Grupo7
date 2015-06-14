#include <vector>

#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "rocaDB/IDB.hpp"
#include "helpers/IPosicionador.hpp"
#include "DataService.hpp"

#include "UserStatus.hpp"
#include "UserProfile.hpp"



TEST_CASE ( "Probar listado de usuario conectados" ) {
    // Mocks
    MockRepository mocker;
    IDB* mockedDB = mocker.Mock<IDB>();
    IPosicionador* mockedPositionator = mocker.Mock<IPosicionador>();

    mocker.OnCall( mockedDB, IDB::Open );
    mocker.OnCall( mockedDB, IDB::Close );

    // Se instancia el "SUT"
    DataService ds( *mockedDB, *mockedPositionator );

    SECTION ( "No hay usuarios conectados" ) {
        std::vector<UserStatus> lUsers = ds.ListActiveUsers();

        REQUIRE ( lUsers.empty() );
    }

    SECTION ( "Un usuario" ) {
        mocker.OnCall( mockedDB, IDB::AutheticateUser ).Return( true );
        mocker.OnCall( mockedDB, IDB::LoadUserFoto ).With( "pepe", Out(":-)") ).Return( true );

        ds.StartSession( "pepe", "1234" );
        std::vector<UserStatus> lUsers = ds.ListActiveUsers();

        REQUIRE ( 1 == lUsers.size() );
        REQUIRE ( "pepe" == lUsers[0].Nombre );
        REQUIRE ( ":-)" == lUsers[0].Foto );
    }

    SECTION ( "varios usuarios" ) {
        mocker.OnCall( mockedDB, IDB::AutheticateUser ).Return( true );
        mocker.OnCall( mockedDB, IDB::LoadUserFoto ).With( _, Out(":-)") ).Return( true );

        ds.StartSession( "pepe", "12" );
        ds.StartSession( "pepa", "123" );
        ds.StartSession( "pepito", "1234" );

        std::vector<UserStatus> lUsers = ds.ListActiveUsers();

        REQUIRE ( 3 == lUsers.size() );
        
        for ( UserStatus us : lUsers ) {
            bool matcheaUnNombreEsperado = ( us.Nombre == "pepe" || us.Nombre == "pepa" || us.Nombre == "pepito" );
            REQUIRE ( matcheaUnNombreEsperado );
        }
    }

}


TEST_CASE ( "Probar modificar la foto del usuario" ) {
    // Mocks
    MockRepository mocker;
    IDB* mockedDB = mocker.Mock<IDB>();
    IPosicionador* mockedPositionator = mocker.Mock<IPosicionador>();

    mocker.OnCall( mockedDB, IDB::Open );
    mocker.OnCall( mockedDB, IDB::Close );
    mocker.OnCall( mockedDB, IDB::AutheticateUser).Return( true );
    mocker.ExpectCall( mockedDB, IDB::StoreUserFoto).With("pepe", ":-P" ).Return( true );

    // Se instancia el "SUT"
    DataService ds( *mockedDB, *mockedPositionator );

    // Se loggea el usuario en el sistema
    unsigned int token = ds.StartSession( "pepe", "1234" );

    ds.ReplaceFoto( token, ":-P" );
}


TEST_CASE ( "Probar checkin del usuario" ) {
    MockRepository mocker;
    IDB* mockedDB = mocker.Mock<IDB>();
    IPosicionador* mockedPositionator = mocker.Mock<IPosicionador>();

    // Expectativas del mock de la base de datos
    mocker.OnCall( mockedDB, IDB::Open );
    mocker.OnCall( mockedDB, IDB::Close );
    mocker.OnCall( mockedDB, IDB::AutheticateUser).Return( true );

    // Se instancia el servicio de datos y se "loggea" al usuario
    DataService ds( *mockedDB, *mockedPositionator );
    unsigned int token = ds.StartSession( "pepe", "1234" );

    SECTION ( "Recuperar checkin" ) {
        // Mockea la llamada y su resultado
        mocker.ExpectCall( mockedDB, IDB::LoadUserUbicacion ).With( "pepe", Out("123.0"), Out("456.0"), Out("1600 2016-07-30") ).Return( true );
        mocker.ExpectCall( mockedPositionator, IPosicionador::getLugarMasCercano ).With( 123.0, 456.0 ).Return( "Narnia" );

        // Act
        std::string ubicacion = ds.GetCheckinLocations(token);

        // Assert
        REQUIRE ( "Narnia" == ubicacion );
    }

    SECTION ( "Guardar coordenadas" ) {
        const double lati = 123.1;
        const double longi = 456.2;
        const std::string fecHora = "21:00hs 2100-12-01";
        const std::string strLat = std::to_string(lati);
        const std::string strLong = std::to_string(longi);

        mocker.ExpectCall( mockedDB, IDB::StoreUserUbicacion ).With( "pepe", strLat, strLong, fecHora ).Return( true );
        
        // Act & assert
        ds.ReplaceCheckinLocation( token, lati, longi, fecHora );
    }
}


TEST_CASE ( "Probar perfil del usuario" ) {
    MockRepository mocker;
    IDB* mockedDB = mocker.Mock<IDB>();
    IPosicionador* mockedPositionator = mocker.Mock<IPosicionador>();

    mocker.OnCall( mockedDB, IDB::Open );
    mocker.OnCall( mockedDB, IDB::Close );
    mocker.OnCall( mockedDB, IDB::AutheticateUser).Return( true );

    // Se instancia el servicio de datos y se "loggea" al usuario
    DataService ds( *mockedDB, *mockedPositionator );
    unsigned int token = ds.StartSession( "pepe", "1234" );

    SECTION ( "El perfil del mismo usuario" ) {
        mocker.autoExpect = false;  // No importa el orden de llamada
        mocker.ExpectCall( mockedDB, IDB::ExistsUser ).With( "pepe" ).Return( true );
        mocker.ExpectCall( mockedDB, IDB::LoadUserUbicacion ).With( "pepe", Out("111"), Out("222"), Out("2015") ).Return( true );
        mocker.ExpectCall( mockedDB, IDB::LoadUserFoto ).With( "pepe", Out("-_-") ).Return( true );
        mocker.ExpectCall( mockedPositionator, IPosicionador::getLugarMasCercano ).With( 111, 222 ).Return( "Hogwarts" );

        // Act
        UserProfile up = ds.GetUserProfile(token, "pepe");

        // Assert
        REQUIRE ( "pepe" == up.Nombre );
        REQUIRE ( "-_-" == up.Foto );
        REQUIRE ( "111" == up.Latitud );
        REQUIRE ( "222" == up.Longitud );
        REQUIRE ( "2015" == up.FechaHora );
        REQUIRE ( "Hogwarts" == up.Ubicacion );
    }

    SECTION ( "El perfil de otro usuario conectado" ) {
        ds.StartSession( "pepito", "4321" );

        mocker.autoExpect = false;  // No importa el orden de llamada
        mocker.ExpectCall( mockedDB, IDB::ExistsUser ).With( "pepito" ).Return( true );
        mocker.ExpectCall( mockedDB, IDB::LoadUserUbicacion ).With( "pepito", Out("111"), Out("222"), Out("2016") ).Return( true );
        mocker.ExpectCall( mockedDB, IDB::LoadUserFoto ).With( "pepito", Out("-_-") ).Return( true );
        mocker.ExpectCall( mockedPositionator, IPosicionador::getLugarMasCercano ).With( 111, 222 ).Return( "Hogwarts" );

        // Act
        UserProfile up = ds.GetUserProfile(token, "pepito");

        // Assert
        REQUIRE ( "pepito" == up.Nombre );
        REQUIRE ( "-_-" == up.Foto );
        REQUIRE ( "111" == up.Latitud );
        REQUIRE ( "222" == up.Longitud );
        REQUIRE ( "2016" == up.FechaHora );
        REQUIRE ( "Hogwarts" == up.Ubicacion );
    }

    SECTION ( "El perfil de otro usuario desconectado" ) {
        mocker.autoExpect = false;  // No importa el orden de llamada
        mocker.ExpectCall( mockedDB, IDB::ExistsUser ).With( "pepito" ).Return( true );
        mocker.ExpectCall( mockedDB, IDB::LoadUserUbicacion ).With( "pepito", Out("111"), Out("222"), Out("2017") ).Return( true );
        mocker.ExpectCall( mockedDB, IDB::LoadUserFoto ).With( "pepito", Out("-_-") ).Return( true );
        mocker.ExpectCall( mockedPositionator, IPosicionador::getLugarMasCercano ).With( 111, 222 ).Return( "Hogwarts" );

        // Act
        UserProfile up = ds.GetUserProfile(token, "pepito");

        // Assert
        REQUIRE ( "pepito" == up.Nombre );
        REQUIRE ( "-_-" == up.Foto );
        REQUIRE ( "111" == up.Latitud );
        REQUIRE ( "222" == up.Longitud );
        REQUIRE ( "2017" == up.FechaHora );
        REQUIRE ( "Hogwarts" == up.Ubicacion );
    }

    SECTION ( "El perfil de un usuario inexistente" ) {
        mocker.autoExpect = false;  // No importa el orden de llamada
        mocker.ExpectCall( mockedDB, IDB::ExistsUser ).Return( false );
        mocker.OnCall( mockedDB, IDB::LoadUserUbicacion ).Return( false );
        mocker.OnCall( mockedDB, IDB::LoadUserFoto ).Return( false );
        mocker.OnCall( mockedPositionator, IPosicionador::getLugarMasCercano ).Return( "" );

        // Act
        UserProfile up = ds.GetUserProfile(token, "pepito");

        // Assert
        REQUIRE ( "" == up.Nombre );
        REQUIRE ( "" == up.Foto );
        REQUIRE ( "" == up.Latitud );
        REQUIRE ( "" == up.Longitud );
        REQUIRE ( "" == up.FechaHora );
        REQUIRE ( "" == up.Ubicacion );
    }
}


