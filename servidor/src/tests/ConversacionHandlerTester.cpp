#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "json/json.h"
#include "IDataService.hpp"

#include "Conversacion.hpp"

#include "Response.hpp"
#include "handlers/ListConversationsRequest.hpp"



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



