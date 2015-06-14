#include <string>
#include <memory>
#include <unordered_map>
#include <functional>

#include <string.h>

#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "IDataService.hpp"
#include "RequestHandlerFactory.hpp"
#include "RequestHandler.hpp"
#include "AuthenticationHandler.hpp"

#include "handlers/EmptyRequest.hpp"
#include "handlers/LoginRequest.hpp"
#include "handlers/LogoutRequest.hpp"
#include "handlers/CheckinHandler.hpp"
#include "handlers/MessageRequest.hpp"
#include "handlers/UserDataRequest.hpp"
#include "handlers/BroadcastHandler.hpp"
#include "handlers/ListUsersRequest.hpp"
#include "handlers/UserSignUpHandler.hpp"
#include "handlers/EditPerfilHandler.hpp"
#include "handlers/SendMessageHandler.hpp"
#include "handlers/ConversationRequest.hpp"
#include "handlers/ListConversationsRequest.hpp"

#include "mocks/MockedRequestHandler.hpp"



TEST_CASE ( "Request handlers esperados" ){
    // Arrange
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    RequestHandlerFactory fac(*mockService);

    SECTION ("Request: GET /grupo7/api/usuarios"){
        const char* method = "GET";
        const char* uri = "/grupo7/api/usuarios";

        std::unique_ptr<RequestHandler> resul = fac.CreateResponder( method, uri );

        // Assert
        REQUIRE ( resul.get() != nullptr );

        ListUsersRequest* castRes = dynamic_cast<ListUsersRequest*>( resul.get() );
        REQUIRE ( castRes != nullptr );
    }

    SECTION ("Request: PUT /grupo7/api/sesion"){
        const char* method = "PUT";
        const char* uri = "/grupo7/api/sesion";

        std::unique_ptr<RequestHandler> resul = fac.CreateResponder( method, uri );

        // Assert
        REQUIRE ( resul.get() != nullptr );

        LoginRequest* castRes = dynamic_cast<LoginRequest*>( resul.get() );
        REQUIRE ( castRes != nullptr );
    }

    SECTION ("Request: POST /grupo7/api/usuarios"){
        const char* method = "POST";
        const char* uri = "/grupo7/api/usuarios";

        std::unique_ptr<RequestHandler> resul = fac.CreateResponder( method, uri );

        // Assert
        REQUIRE ( resul.get() != nullptr );

        UserSignUpHandler* castRes = dynamic_cast<UserSignUpHandler*>( resul.get() );
        REQUIRE ( castRes != nullptr );
    }

    SECTION ( "Request: PUT /grupo7/api/usuarios" ) {
        const char* method = "PUT";
        const char* uri = "/grupo7/api/usuarios";

        std::unique_ptr<RequestHandler> resul = fac.CreateResponder( method, uri );
        
        // Assert
        REQUIRE ( resul.get() != nullptr );

        EditPerfilHandler* castRes = dynamic_cast<EditPerfilHandler*>( resul.get() );
        REQUIRE ( castRes != nullptr );
    }

    SECTION ( "Request: DELETE /grupo7/api/sesion" ) {
        const char* method = "DELETE";
        const char* uri = "/grupo7/api/sesion";

        std::unique_ptr<RequestHandler> resul = fac.CreateResponder( method, uri );

        // Assert
        REQUIRE ( resul.get() != nullptr );

        LogoutRequest* castRes = dynamic_cast<LogoutRequest*>( resul.get() );
        REQUIRE ( castRes != nullptr );
    }

    SECTION ( "Request: GET /grupo7/api/usuario" ) {
        const char* method = "GET";
        const char* uri = "/grupo7/api/usuario";

        std::unique_ptr<RequestHandler> resul = fac.CreateResponder( method, uri );

        // Assert
        REQUIRE ( resul.get() != nullptr );

        UserDataRequest* castRes = dynamic_cast<UserDataRequest*>( resul.get() );
        REQUIRE ( castRes != nullptr );
    }

    SECTION ( "Request: GET /grupo7/api/conversaciones" ) {
        const char* method = "GET";
        const char* uri = "/grupo7/api/conversaciones";

        std::unique_ptr<RequestHandler> resul = fac.CreateResponder( method, uri );

        // Assert
        REQUIRE ( resul.get() != nullptr );

        ListConversationsRequest* castRes = dynamic_cast<ListConversationsRequest*>( resul.get() );
        REQUIRE ( castRes != nullptr );
    }

    SECTION ( "Request: GET /grupo7/api/conversacion" ) {
        const char* method = "GET";
        const char* uri = "/grupo7/api/conversacion";

        std::unique_ptr<RequestHandler> resul = fac.CreateResponder( method, uri );

        // Assert
        REQUIRE ( resul.get() != nullptr );

        ConversationRequest* castRes = dynamic_cast<ConversationRequest*>( resul.get() );
        REQUIRE ( castRes != nullptr );
    }

    SECTION ( "Request: POST /grupo7/api/checkin" ) {
        const char* method = "POST";
        const char* uri = "/grupo7/api/checkin";

        std::unique_ptr<RequestHandler> resul = fac.CreateResponder( method, uri );

        // Assert
        REQUIRE ( resul.get() != nullptr );

        CheckinHandler* castRes = dynamic_cast<CheckinHandler*>( resul.get() );
        REQUIRE ( castRes != nullptr );
    }

    SECTION ( "Request: POST /grupo7/api/broadcast" ) {
        const char* method = "POST";
        const char* uri = "/grupo7/api/broadcast";

        std::unique_ptr<RequestHandler> resul = fac.CreateResponder( method, uri );

        // Assert
        REQUIRE ( resul.get() != nullptr );

        BroadcastHandler* castRes = dynamic_cast<BroadcastHandler*>( resul.get() );
        REQUIRE ( castRes != nullptr );
    }

    SECTION ( "Request: POST /grupo7/api/mensajes" ) {
        const char* method = "POST";
        const char* uri = "/grupo7/api/mensajes";

        std::unique_ptr<RequestHandler> resul = fac.CreateResponder( method, uri );

        // Assert
        REQUIRE ( resul.get() != nullptr );

        SendMessageHandler* castRes = dynamic_cast<SendMessageHandler*>( resul.get() );
        REQUIRE ( castRes != nullptr );
    }

    SECTION ( "Request: GET /grupo7/api/mensajes" ) {
        const char* method = "GET";
        const char* uri = "/grupo7/api/mensajes";

        std::unique_ptr<RequestHandler> resul = fac.CreateResponder( method, uri );

        // Assert
        REQUIRE ( resul.get() != nullptr );

        MessageRequest* castRes = dynamic_cast<MessageRequest*>( resul.get() );
        REQUIRE ( castRes != nullptr );
    }

}



TEST_CASE ( "Crear manejador de autenticacion" ){
    // Arrange
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    RequestHandlerFactory fac(*mockService);

    size_t dataLen = 0;
    const char* data = nullptr;
    const char* queryString = nullptr;

    // Act
    std::unique_ptr<AuthenticationHandler> auHandler = fac.CreateRequestAuthenticator(queryString, data, dataLen);

    // Assert
    REQUIRE ( auHandler.get() != nullptr );
}



TEST_CASE ( "Request no esperado" ){
    // Arrange
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();
    RequestHandlerFactory fac(*mockService);


    SECTION ( "URI invalida" ){
        const char* uri = "/grupo7/api/cthulhu";
        const char* method = "GET";
        
        std::unique_ptr<RequestHandler> resul = fac.CreateResponder( method, uri );

        REQUIRE ( resul.get() != nullptr );

        EmptyRequest* castRes = dynamic_cast<EmptyRequest*>( resul.get() );
        REQUIRE ( castRes != nullptr );
    }


    SECTION ( "Method invalido" ){
        const char* uri = "/grupo7/api/usuarios";
        const char* method = "JUMP";

        std::unique_ptr<RequestHandler> resul = fac.CreateResponder( method, uri );

        REQUIRE ( resul.get() != nullptr );

        EmptyRequest* castRes = dynamic_cast<EmptyRequest*>( resul.get() );
        REQUIRE ( castRes != nullptr );
    }


    SECTION ( "Method y URI invalidos" ){
        const char* uri = "/grupo7/api/cthulhu";
        const char* method = "RUN";

        std::unique_ptr<RequestHandler> resul = fac.CreateResponder( method, uri );

        REQUIRE ( resul.get() != nullptr );

        EmptyRequest* castRes = dynamic_cast<EmptyRequest*>( resul.get() );
        REQUIRE ( castRes != nullptr );
    }
}


TEST_CASE ( "Prueba simple de mockeo de interfaces" ){
    // Mocks
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    // Params
    const char* uri = "/grupo7/api/usuarios";
    const char* method = "GET";

    // Act & Assert
    REQUIRE_NOTHROW (
        RequestHandlerFactory fac(*mockService);
    );
}


TEST_CASE( "Manejo de char pointers", "[punteros][params]" ){

    SECTION ( "char array a string" ){
        const char* p1 = "GET";
        std::string s( p1 );

        CHECK ( s == p1 );
        CHECK ( strcmp( s.c_str(), p1 ) == 0 );
    }

    SECTION ( "char array dinamico a string" ){
        const char* pSrc = "POST";
        int tam =  strlen(pSrc);

        char* pDst = new char[ tam +1 ];    // Mas el null
        strcpy( pDst, pSrc );

        std::string s( pDst );

        CHECK ( s == pDst );
        CHECK ( strcmp( pSrc, pDst ) == 0);
        CHECK ( strcmp( s.c_str(), pDst ) == 0 );

        delete[] pDst;
    }

}


TEST_CASE ( "Nueva inplemetación para la factory" ){
    SECTION ( "Simple mapa" ){
        std::unordered_map< std::string, std::function<int(void)> > um;
        um["cinco"] = []{ return 5; };

        int resul = 0;
        REQUIRE_NOTHROW (
            resul = um["cinco"]();
        );

        REQUIRE ( 5 == resul );
    }

    SECTION ( "Simple mapa con parametro" ){
        std::unordered_map< std::string, std::function<int(int)> > um;
        um["fun"] = [] (int a) { return a; };

        int resul = 0;
        REQUIRE_NOTHROW (
            resul = um["fun"]( 9 );
        );

        REQUIRE ( 9 == resul );
    }

    SECTION ( "Mapa que devuelve un puntero" ){
        std::unordered_map< int, std::function< int*(void) > > um;
        um[1] = []{ return new int; };

        int* resul = nullptr;
        REQUIRE_NOTHROW (
            resul = um[1]();
        );

        REQUIRE ( nullptr != resul );

        delete resul;
    }

    SECTION ( "Mapa que devuelve un int y recibe una interfaz" ){
        // Mocks
        MockRepository mocker;
        IDataService* mockService = mocker.Mock<IDataService>();
        mocker.OnCall( mockService, IDataService::StartSession ).Return( 999 );

        std::unordered_map< int, std::function<unsigned int(IDataService&)> > um;
        um[1] = [] (IDataService& ds) { 
            return ds.StartSession("", "");
        };

        unsigned int resul;
        REQUIRE_NOTHROW (
            resul = um[1](*mockService);
        );

        REQUIRE ( 999 == resul );
    }

    SECTION ( "Mapa que devuelve un puntero a una clase base" ){
        // Arrange
        MockRepository mocker;
        IDataService* mockService = mocker.Mock<IDataService>();

        // Act
        std::unordered_map< int, std::function< RequestHandler*(IDataService&) > > um;
        um[1] = [] (IDataService& ds) -> RequestHandler* { return new MockedRequestHandler(ds); };

        // Assert
        RequestHandler* rh = nullptr;
        REQUIRE_NOTHROW (
                rh = um[1]( *mockService );
        );

        REQUIRE ( nullptr != rh );

        delete rh;
    }

    SECTION ( "Mapa que se pide un labmda inexistente" ){
        std::unordered_map< int, std::function<int(int)> > um;
        um[1] = [] (int i) { return i; };

        auto ptrResul = um.find( 99 );

        REQUIRE ( um.end() == ptrResul );

    }

}


