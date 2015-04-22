#include <memory>

#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "IDataService.hpp"

#include "handlers/EmptyRequest.hpp"
#include "handlers/ListUsersRequest.hpp"
#include "handlers/AuthenticateUserRequest.hpp"



TEST_CASE ( "Probar la carga de parametros en el handler vacio" ){
    // Mocks
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    std::unique_ptr<EmptyRequest> req( new EmptyRequest(*mockService) );

    SECTION ( "Aceptar los parametros" ){
        const char* testData = "pepepepe";
        char* cData = new char[ strlen(testData) +1 ];
        strcpy(cData, testData);

        size_t cDataLen = strlen(testData) +1;
        const char* qStr = "nombre=pepe";

        REQUIRE_NOTHROW(
            req->LoadParameters( qStr, cData, cDataLen );
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
            req->LoadParameters( qStr, cData, cDataLen );
        );

        delete[] cData;
    }

    SECTION ( "Aceptar los parametros: sin content data" ){
        char* cData = nullptr;
        size_t cDataLen = 0;
        const char* qStr = "nombre=pepe";

        REQUIRE_NOTHROW(
            req->LoadParameters( qStr, cData, cDataLen );
        );
    }

    SECTION ( "Aceptar los parametros: no hay parametros a cargar" ){
        size_t cDataLen = 0;
        char* cData = nullptr;
        const char* qStr = nullptr;

        REQUIRE_NOTHROW(
            req->LoadParameters( qStr, cData, cDataLen );
        );
    }

}



