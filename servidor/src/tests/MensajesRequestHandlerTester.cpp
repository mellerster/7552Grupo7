#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "json/json.h"
#include "IDataService.hpp"

#include "Response.hpp"

#include "handlers/MessageRequest.hpp"
#include "handlers/BroadcastHandler.hpp"
#include "handlers/SendMessageHandler.hpp"

#include "handlers/dtos/MensajeDTO.hpp"
#include "handlers/dtos/BroadcastDTO.hpp"
#include "handlers/dtos/SentMensajeDTO.hpp"
#include "handlers/dtos/ListaMensajesDTO.hpp"



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
    // Mocks
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();
    
    const char* queryString = nullptr;
    const char* data = "{ \"Token\" : 99, \"IDConversacion\" : 11,  \"Texto\" : \"Amadeus\" }";
    const size_t dataLen = strlen(data) +1;

    // Creates the handler and parses its parameters
    SendMessageHandler handler( *mockService );
    handler.LoadParameters( queryString, data, dataLen );

    SECTION ( "Invalid token" ) {
        mocker.ExpectCall( mockService, IDataService::IsTokenActive ).With( 99 ).Return( false );

        // Act
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 403 == resp.GetStatus() );
    }

    SECTION ( "Exito" ) {
        mocker.ExpectCall( mockService, IDataService::IsTokenActive ).With( 99 ).Return( true );
        mocker.ExpectCall( mockService, IDataService::AgregarMensaje ).With( 99, 11, "Amadeus" ).Return( true );

        // Act
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 200 == resp.GetStatus() );
    }

    SECTION ( "Fracaso" ) {
        mocker.ExpectCall( mockService, IDataService::IsTokenActive ).With( 99 ).Return( true );
        mocker.ExpectCall( mockService, IDataService::AgregarMensaje ).With( 99, 11, "Amadeus" ).Return( false );

        // Act
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 500 == resp.GetStatus() );
    }
}


TEST_CASE ( "Message request tests" ) {
    // Mocks
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();
    
    const char* data = nullptr;
    const size_t dataLen = 0;
    const char* queryString = "Token=99&IDConversacion=11";

    // Creates the handler and parses its parameters
    MessageRequest handler( *mockService );
    handler.LoadParameters( queryString, data, dataLen );

    SECTION ( "Invalid token" ) {
        mocker.ExpectCall( mockService, IDataService::IsTokenActive ).With( 99 ).Return( false );

        // Act
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 403 == resp.GetStatus() );
    }

    SECTION ( "Exito" ) {
        Mensaje m;
        m.Texto = "hola";
        m.IDRemitente = "Mio";

        std::vector<Mensaje> noLeidos;
        noLeidos.push_back( m );

        mocker.ExpectCall( mockService, IDataService::IsTokenActive ).With( 99 ).Return( true );
        mocker.ExpectCall( mockService, IDataService::GetMensajesNoLeidos ).With( 99, 11 ).Return( noLeidos );

        // Act
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 200 == resp.GetStatus() );
    }

    SECTION ( "No hay mensajes no leidos" ) {
        std::vector<Mensaje> noLeidos;
        mocker.ExpectCall( mockService, IDataService::IsTokenActive ).With( 99 ).Return( true );
        mocker.ExpectCall( mockService, IDataService::GetMensajesNoLeidos ).With( 99, 11 ).Return( noLeidos );

        // Act
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 200 == resp.GetStatus() );
    }
}



