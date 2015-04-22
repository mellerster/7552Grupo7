#include <string>
#include <string.h>
#include <memory>

#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "IDataService.hpp"
#include "RequestHandlerFactory.hpp"
#include "RequestHandler.hpp"

#include "handlers/EmptyRequest.hpp"
#include "handlers/ListUsersRequest.hpp"
#include "handlers/AuthenticateUserRequest.hpp"



TEST_CASE ( "Request handlers esperados" ){
    // Arrange
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();
    RequestHandlerFactory fac(*mockService);

    SECTION ("Crear List users request"){
        const char* method = "GET";
        const char* uri = "/grupo7/api/usuarios";

        std::unique_ptr<RequestHandler> resul = fac.CreateResponder( method, uri );

        // Assert
        REQUIRE ( resul.get() != nullptr );

        ListUsersRequest* castRes = dynamic_cast<ListUsersRequest*>( resul.get() );
        REQUIRE ( castRes != nullptr );
    }

    SECTION ("Crear autheticate user request"){
        const char* method = "PUT";
        const char* uri = "/grupo7/api/sesion";

        std::unique_ptr<RequestHandler> resul = fac.CreateResponder( method, uri );

        // Assert
        REQUIRE ( resul.get() != nullptr );

        AuthenticateUserRequest* castRes = dynamic_cast<AuthenticateUserRequest*>( resul.get() );
        REQUIRE ( castRes != nullptr );
    }
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


