#include <vector>

#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "rocaDB/IDB.hpp"
#include "posicionaitor/IPosicionador.hpp"
#include "DataService.hpp"

#include "UserStatus.hpp"



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
            if ( us.Nombre == "pepe" || us.Nombre == "pepa" ||us.Nombre == "pepito" ) {
                REQUIRE ( true );

            } else {
                REQUIRE ( false );
            }
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
        mocker.ExpectCall( mockedDB, IDB::LoadUserUbicacion ).With( "pepe", Out("123.0"), Out("456.0") ).Return( true );
        mocker.ExpectCall( mockedPositionator, IPosicionador::getLugarMasCercano ).With( 123.0, 456.0 ).Return( "Narnia" );

        // Act
        std::string ubicacion = ds.GetCheckinLocations(token);

        // Assert
        REQUIRE ( "Narnia" == ubicacion );
    }

    SECTION ( "Guardar coordenadas" ) {
        const double lati = 123.1;
        const double longi = 456.2;
        const std::string strLat = std::to_string(lati);
        const std::string strLong = std::to_string(longi);

        mocker.ExpectCall( mockedDB, IDB::StoreUserUbicacion ).With( "pepe", strLat, strLong ).Return( true );
        
        // Act & assert
        ds.ReplaceCheckinLocation( token, lati, longi );
    }
}



