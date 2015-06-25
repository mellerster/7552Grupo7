#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "IDataService.hpp"
#include "AuthenticationHandler.hpp"



TEST_CASE ( "Autenticador de pedidos - POST" ){
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    const char* queryString = nullptr;
    const char* data = "{ \"Token\" : 1, \"NombreUsuario\" : \"pepe\", \"Password\" : \"1234\" }";
    const size_t dataLen = strlen(data) +1;

    AuthenticationHandler auHand( *mockService );

    SECTION ( "Cargar params" ){
        REQUIRE_NOTHROW (
            auHand.LoadParameters( queryString, data, dataLen );
        );
    }

    SECTION ( "Autenticacion token - OK" ){
        // Act
        auHand.LoadParameters( queryString, data, dataLen );
        bool isOK = auHand.IsResourceAccesible( "no importa", "no importa" );

        // Assert
        REQUIRE ( isOK );
    }
}


TEST_CASE ( "Autenticador de pedidos - GET" ){
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    const char* queryString = "Token=44";
    const char* data = nullptr;
    const size_t dataLen = 0;

    AuthenticationHandler auHand( *mockService );

    SECTION ( "Cargar params" ){
        REQUIRE_NOTHROW (
            auHand.LoadParameters( queryString, data, dataLen );
        );
    }

    SECTION ( "Autenticacion token - OK" ){
        // Act
        auHand.LoadParameters( queryString, data, dataLen );
        bool isOK = auHand.IsResourceAccesible( "no importa", "no importa" );

        // Assert
        REQUIRE ( isOK );
    }
}

