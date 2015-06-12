#include <string.h>
#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "IDataService.hpp"

#include "handlers/LoginRequest.hpp"
#include "handlers/LogoutRequest.hpp"



TEST_CASE ( "Testeo de login requests - Parseo de params" ){
    // Mocks
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    LoginRequest lr( *mockService );

    SECTION ( "Seteo de parametros" ){
        // Params
        const char* queryString = nullptr;
        const char* data = "{ \"Token\" : 1 }";
        size_t dataLen = strlen(data) +1;

        REQUIRE_NOTHROW (
                lr.LoadParameters( queryString, data, dataLen );
        );
    }

    SECTION ( "Extraccion de params" ){
        const char* queryString = nullptr;
        const char* data = "{ \"Token\" : 0, \"NombreUsuario\" : \"pepe\", \"Password\" : \"123\" }";
        size_t dataLen = strlen(data) +1;

        // Solo comienza la sesion si es es nombre de usuario y password que especificamos
        mocker.OnCall( mockService, IDataService::StartSession ).Return( 0 );
        mocker.OnCall( mockService, IDataService::StartSession ).With("pepe", "123").Return( 5555 );

        // Act
        lr.LoadParameters( queryString, data, dataLen );
        Response resp = lr.GetResponseData();

        // Assert
        REQUIRE ( 200 == resp.GetStatus() );
    }

    SECTION ( "Probar usuario invalido" ){
        const char* queryString = nullptr;
        const char* data = "{ \"Token\" : 0, \"NombreUsuario\" : \"pepe\", \"Password\" : \"123\" }";
        size_t dataLen = strlen(data) +1;

        mocker.OnCall( mockService, IDataService::StartSession ).Return( 0 );

        // Act
        lr.LoadParameters( queryString, data, dataLen );
        Response resp = lr.GetResponseData();

        // Assert
        REQUIRE ( 403 == resp.GetStatus() );
    }

    SECTION ( "Probar usuario valido" ){
        const char* queryString = nullptr;
        const char* data = "{ \"Token\" : 0, \"NombreUsuario\" : \"pepe\", \"Password\" : \"123\" }";
        size_t dataLen = strlen(data) +1;

        // Solo comienza la sesion si es es nombre de usuario y password que especificamos
        mocker.OnCall( mockService, IDataService::StartSession ).Return( 5555 );

        // Act
        lr.LoadParameters( queryString, data, dataLen );
        Response resp = lr.GetResponseData();

        // Assert
        REQUIRE ( 200 == resp.GetStatus() );
    }
}


TEST_CASE ( "Handler de logout" ) {
    // Arrange
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();
    mocker.ExpectCall( mockService, IDataService::EndSession );

    LogoutRequest lr( *mockService );

    SECTION ( "Token valido" ) {
        const char* queryString = nullptr;
        const char* data = "{ \"Token\" : 123456 }";
        size_t dataLen = strlen(data) +1;

        lr.LoadParameters( queryString, data, dataLen );

        // Act
        Response res = lr.GetResponseData();

        // Assert
        REQUIRE ( 200 == res.GetStatus() );
    }

    SECTION ( "Token invalido" ) {
        const char* queryString = nullptr;
        const char* data = "{ \"Token\" : 0 }";
        size_t dataLen = strlen(data) +1;

        lr.LoadParameters( queryString, data, dataLen );

        // Act
        Response res = lr.GetResponseData();

        // Assert
        REQUIRE ( 200 == res.GetStatus() );
    }

}



