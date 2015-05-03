#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "IDataService.hpp"
#include "AuthenticationHandler.hpp"



TEST_CASE ( "Autenticador de pedidos" ){
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    const char* queryString =nullptr;
    const char* data = "{ \"Token\" : 1, \"NombreUsuario\" : \"pepe\", \"Password\" : \"1234\" }";
    size_t dataLen = strlen(data) +1;

    AuthenticationHandler auHand( *mockService );

    SECTION ( "Cargar params" ){
        REQUIRE_NOTHROW (
            auHand.LoadParameters( queryString, data, dataLen );
        );
    }

    SECTION ( "Autenticacion token - OK" ){
        // Arrange
        mocker.OnCall( mockService, IDataService::IsTokenActive ).Return( true );

        // Act
        auHand.LoadParameters( queryString, data, dataLen );
        bool isOK = auHand.IsResourceAccesible( "no importa", "no importa" );

        // Assert
        REQUIRE ( true == isOK );
    }

    SECTION ( "Autenticacion token - nope" ){
        // Arrange
        mocker.OnCall( mockService, IDataService::IsTokenActive ).Return( true );
        mocker.OnCall( mockService, IDataService::IsTokenActive ).With( 1 ).Return( false );

        // Act
        auHand.LoadParameters( queryString, data, dataLen );
        bool isOK = auHand.IsResourceAccesible( "no importa", "no importa" );

        // Assert
        //REQUIRE ( false == isOK );
    }
}


