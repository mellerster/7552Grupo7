#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "IDataService.hpp"

#include "Response.hpp"
#include "handlers/EmptyRequest.hpp"
#include "handlers/ListUsersRequest.hpp"
#include "handlers/LoginRequest.hpp"

#include "mocks/MockedRequestHandler.hpp"



TEST_CASE ( "Fake test de Request handler base" ){
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    MockedRequestHandler mReqHand( *mockService );


    SECTION ( "Load nada" ){
        REQUIRE_NOTHROW (
            mReqHand.LoadParameters(nullptr, nullptr, 0);
        );
    }

    SECTION ( "Load query string" ){
        const char* qString = "uno=1";

        REQUIRE_NOTHROW (
            mReqHand.LoadParameters(qString, nullptr, 0);
        );
    }

    SECTION ( "Load content data" ){
        const char* data = "{ \"dos\": 2 }";
        size_t tam = strlen( data ) +1; // Null terminator

        REQUIRE_NOTHROW (
            mReqHand.LoadParameters(nullptr, data, tam);
        );
    }

    SECTION ( "Load query string and content data" ){
        const char* qString = "tres=3";
        const char* data = "{ \"cuatro\": 4 }";
        size_t tam = strlen( data ) +1; // Null terminator

        REQUIRE_NOTHROW (
            mReqHand.LoadParameters(qString, data, tam);
        );
    }

}



TEST_CASE ( "Testeo de list users requests" ){
    // Mocks
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    ListUsersRequest lur( *mockService );

    SECTION ( "Seteo de parametros" ){
        // Params
        size_t dataLen = 0;
        const char* data = nullptr;
        const char* queryString = "Token=1";

        REQUIRE_NOTHROW (
                lur.LoadParameters( queryString, data, dataLen );
        );
    }
}



TEST_CASE ( "Testeo de login requests" ){
    // Mocks
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    LoginRequest lr( *mockService );

    SECTION ( "Seteo de parametros" ){
        // Params
        size_t dataLen = 0;
        const char* data = nullptr;
        const char* queryString = "Token=1";

        REQUIRE_NOTHROW (
                lr.LoadParameters( queryString, data, dataLen );
        );
    }
}



TEST_CASE ( "Probar la carga de parametros en el handler vacio" ){
    // Mocks
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    EmptyRequest req( *mockService );

    SECTION ( "Aceptar los parametros" ){
        const char* testData = "pepepepe";
        char* cData = new char[ strlen(testData) +1 ];
        strcpy(cData, testData);

        size_t cDataLen = strlen(testData) +1;
        const char* qStr = "nombre=pepe";

        REQUIRE_NOTHROW(
            req.LoadParameters( qStr, cData, cDataLen );
        );

        delete[] cData;
    }

    SECTION ( "Aceptar los parametros: sin query string" ){
        const char* testData = "pepepepe";
        char* cData = new char[ strlen(testData) +1 ];
        strcpy(cData, testData);
        size_t cDataLen = strlen(testData) +1;

        const char* qStr = nullptr;

        REQUIRE_NOTHROW(
            req.LoadParameters( qStr, cData, cDataLen );
        );

        delete[] cData;
    }

    SECTION ( "Aceptar los parametros: sin content data" ){
        char* cData = nullptr;
        size_t cDataLen = 0;
        const char* qStr = "nombre=pepe";

        REQUIRE_NOTHROW(
            req.LoadParameters( qStr, cData, cDataLen );
        );
    }

    SECTION ( "Aceptar los parametros: no hay parametros a cargar" ){
        size_t cDataLen = 0;
        char* cData = nullptr;
        const char* qStr = nullptr;

        REQUIRE_NOTHROW(
            req.LoadParameters( qStr, cData, cDataLen );
        );
    }

    SECTION ( "El request es vacio porque el recursos pedido no existe" ){
        Response resp = req.GetResponseData();

        REQUIRE ( 404 == resp.GetStatus() );
    }
}




