#include "include/catch.hpp"
#include "include/hippomocks.h"

#include <vector>

#include "json/json.h"
#include "IDataService.hpp"

#include "Response.hpp"
#include "handlers/ListUsersRequest.hpp"



TEST_CASE ( "Testeo de list users requests - Manejo de resultados" ){
    // Arrange
    size_t dataLen = 0;
    const char* data = nullptr;
    const char* queryString = "Token=999";

    // Mocks
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    ListUsersRequest lur( *mockService );
    lur.LoadParameters( queryString, data, dataLen );

    SECTION ( "Token invalido - forbidden" ){
        std::vector<UserStatus> vUsers;
        mocker.ExpectCall( mockService, IDataService::IsTokenActive).Return( false );
        mocker.OnCall( mockService, IDataService::ListActiveUsers).Return( vUsers );

        // Act
        Response resp = lur.GetResponseData();

        // Assert
        REQUIRE ( 403 == resp.GetStatus() );
    }

    SECTION ( "Token valido" ){
        std::vector<UserStatus> vUsers;
        mocker.ExpectCall( mockService, IDataService::IsTokenActive).Return( true );
        mocker.OnCall( mockService, IDataService::ListActiveUsers).Return( vUsers );

        // Act
        Response resp = lur.GetResponseData();

        // Assert
        REQUIRE ( 200 == resp.GetStatus() );
    }

    SECTION ( "Chequear datos" ){
        UserStatus us;
        us.Nombre = "Pepe";
        us.Estado = "Living la vida loca";

        std::vector<UserStatus> vUsers;
        vUsers.push_back( us );

        mocker.ExpectCall( mockService, IDataService::IsTokenActive).Return( true );
        mocker.ExpectCall( mockService, IDataService::ListActiveUsers).Return( vUsers );

        // Act
        Response resp = lur.GetResponseData();
        const char* resul = resp.GetData();

        // Assert
        Json::Value jn(resul);
        REQUIRE ( 200 == resp.GetStatus() );

        REQUIRE ( Json::ValueType::objectValue == jn.type() );
        REQUIRE ( Json::ValueType::arrayValue == jn["Usuarios"].type() );
        REQUIRE ( 1 == jn["Usuarios"].size() );

        Json::Value jnUsu = jn["Usuarios"][0];
        REQUIRE ( us.Nombre == jnUsu["Nombre"].asString() );
        REQUIRE ( us.Estado == jnUsu["Estado"].asString() );

        delete[] resul;
    }

}


TEST_CASE ( "Testeo de list users requests - Parseo de params" ){
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

    SECTION ( "Seteo de parametros incorrectos" ){
        const char* queryString = nullptr;
        const char* data = "Token=1";
        size_t dataLen = strlen(data) +1;

        REQUIRE_THROWS(
                lur.LoadParameters( queryString, data, dataLen );
        );
    }

}


