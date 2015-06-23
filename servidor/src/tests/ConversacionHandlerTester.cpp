#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "json/json.h"
#include "IDataService.hpp"

#include "Conversacion.hpp"

#include "Response.hpp"
#include "handlers/ListConversationsRequest.hpp"
#include "handlers/ConversationRequest.hpp"



TEST_CASE ( "Obtener el listado de conversaciones") {
    // Mocks
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();
    
    const size_t dataLen = 0;
    const char* data = nullptr;
    const char* queryString = "Token=999";

    ListConversationsRequest handler( *mockService );
    handler.LoadParameters( queryString, data, dataLen );

    SECTION ( "No hay conversaciones" ) {
        std::vector<Conversacion> vecConvs;

        mocker.OnCall( mockService, IDataService::IsTokenActive ).Return( true );
        mocker.OnCall( mockService, IDataService::ListActiveConversations ).Return( vecConvs );

        // Act
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 200 == resp.GetStatus() );
    }

    SECTION ( "Hay conversaciones" ) {
        Conversacion c1;
        c1.IDConversacion = 1;
        c1.UltimoMensaje = "Afraid of the clown";
        c1.UltimoMensajeLeido = false;

        Conversacion c2;
        c2.IDConversacion = 22;
        c2.UltimoMensaje = "RollerCoster";
        c2.UltimoMensajeLeido = true;

        std::vector<Conversacion> vecConvs;
        vecConvs.push_back( c1 );
        vecConvs.push_back( c2 );

        mocker.OnCall( mockService, IDataService::IsTokenActive ).Return( true );
        mocker.OnCall( mockService, IDataService::ListActiveConversations ).Return( vecConvs );

        // Act
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 200 == resp.GetStatus() );
    }

    SECTION ( "Invalid token" ) {
        mocker.OnCall( mockService, IDataService::IsTokenActive ).Return( false );

        // Act
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 403 == resp.GetStatus() );
    }
}


TEST_CASE ( "Conversacion handler" ) {
    // Mocks
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    const size_t dataLen = 0;
    const char* data = nullptr;

    ConversationRequest handler( *mockService );

    SECTION ( "Con ID de conversacion" ) {
        const char* queryString = "Token=999&IDConversacion=888";
        handler.LoadParameters( queryString, data, dataLen );

        std::vector<std::string> vecPartis;
        vecPartis.push_back( "pepa" );

        Mensaje m;
        m.Texto = "Squirels in my pants";
        m.IDRemitente = "Squirels";

        std::vector<Mensaje> vecMsgs;
        vecMsgs.push_back( m );
    
        mocker.OnCall( mockService, IDataService::IsTokenActive ).Return( true );
        mocker.OnCall( mockService, IDataService::GetParticipantes ).With( 999, 888 ).Return( vecPartis );
        mocker.OnCall( mockService, IDataService::GetMensajes ).With( 999, 888 ).Return( vecMsgs );

        // Act
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 200 == resp.GetStatus() );
    }

    SECTION ( "Con user ID" ) {
        const char* queryString = "Token=999&IDUsuario=pepa";
        handler.LoadParameters( queryString, data, dataLen );

        Mensaje m;
        m.Texto = "Squirels in my pants";
        m.IDRemitente = "Squirels";

        std::vector<Mensaje> vecMsgs;
        vecMsgs.push_back( m );

        mocker.OnCall( mockService, IDataService::IsTokenActive ).Return( true );
        mocker.OnCall( mockService, IDataService::GetConversacion ).With( 999, "pepa" ).Return( 22 );
        mocker.OnCall( mockService, IDataService::GetMensajes ).With( 999, 22 ).Return( vecMsgs );

        // Act
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 200 == resp.GetStatus() );
    }

    SECTION ( "Invalid token" ) {
        const char* queryString = "Token=999";
        mocker.OnCall( mockService, IDataService::IsTokenActive ).Return( false );

        handler.LoadParameters( queryString, data, dataLen );

        // Act
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 403 == resp.GetStatus() );
    }
}




