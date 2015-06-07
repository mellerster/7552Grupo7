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
        mocker.OnCall( mockedDB, IDB::LoadUserFoto ).Do( [] (std::string user, std::string& foto) {
                    foto = ":-)";
                    return true;
                } );

        ds.StartSession( "pepe", "1234" );
        std::vector<UserStatus> lUsers = ds.ListActiveUsers();

        REQUIRE ( 1 == lUsers.size() );
        REQUIRE ( "pepe" == lUsers[0].Nombre );
        REQUIRE ( ":-)" == lUsers[0].Foto );
    }

    SECTION ( "varios usuarios" ) {
        mocker.OnCall( mockedDB, IDB::AutheticateUser ).Return( true );
        mocker.OnCall( mockedDB, IDB::LoadUserFoto ).Do( [] (std::string user, std::string& foto) {
                    foto = ":-)";
                    return true;
                } );

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


