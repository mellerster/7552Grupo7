#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "IDataService.hpp"
#include "Response.hpp"
#include "handlers/UserSignUpHandler.hpp"



TEST_CASE ( "Testear Registracion de usuario" ){
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    UserSignUpHandler reg( *mockService );

    SECTION ( "Seteo de params - OK" ){
        const char* queryString = nullptr;
        const char* data = "{ \"NombreUsuario\" : \"pepe\", \"Password\" : \"1234\" }";
        size_t dataLen = strlen(data) +1;

        REQUIRE_NOTHROW (
                reg.LoadParameters( queryString, data, dataLen )
        );
    }

    SECTION ( "Seteo de params - nope" ){
        const char* queryString = nullptr;
        const char* data = nullptr;
        size_t dataLen = 0;

        REQUIRE_NOTHROW (
                reg.LoadParameters( queryString, data, dataLen )
        );
    }

    SECTION ( "Testear resultado" ){
        const char* queryString =nullptr;
        const char* data = "{ \"NombreUsuario\" : \"pepe\", \"Password\" : \"1234\" }";
        size_t dataLen = strlen(data) +1;

        reg.LoadParameters( queryString, data, dataLen );
        Response resp = reg.GetResponseData();

        REQUIRE ( 200 == resp.GetStatus() );
    }

}


