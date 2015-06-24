#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "json/json.h"
#include "IDataService.hpp"

#include "Response.hpp"

#include "handlers/BroadcastHandler.hpp"
#include "handlers/dtos/BroadcastDTO.hpp"



TEST_CASE ( "Testear broadcast de mensajes" ) {
    // Mocks
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();
    
    const char* queryString = nullptr;
    const char* data = "{ \"Token\" : 99, \"Mensaje\" : \"lazy\" }";
    const size_t dataLen = strlen(data) +1;

    // Creates the handler and parses its parameters
    BroadcastHandler handler( *mockService );
    handler.LoadParameters( queryString, data, dataLen );

    SECTION ( "Invalid token" ) {
        mocker.ExpectCall( mockService, IDataService::IsTokenActive ).With( 99 ).Return( false );

        // Act
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 403 == resp.GetStatus() );
    }

    SECTION ( "Success" ) {
        mocker.ExpectCall( mockService, IDataService::IsTokenActive ).With( 99 ).Return( true );
        mocker.ExpectCall( mockService, IDataService::EnviarBroadcast ).With( 99, "lazy" ).Return( true );

        // Act
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 200 == resp.GetStatus() );
    }

    SECTION ( "Server error" ) {
        mocker.ExpectCall( mockService, IDataService::IsTokenActive ).With( 99 ).Return( true );
        mocker.ExpectCall( mockService, IDataService::EnviarBroadcast ).With( 99, "lazy" ).Return( false );

        // Act
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 500 == resp.GetStatus() );
    }
}



TEST_CASE ( "Testear envio de mensajes" ) {
}



