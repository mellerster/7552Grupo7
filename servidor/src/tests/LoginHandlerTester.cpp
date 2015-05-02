#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "IDataService.hpp"

#include "handlers/LoginRequest.hpp"



TEST_CASE ( "Testeo de login requests - Parseo de params" ){
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



