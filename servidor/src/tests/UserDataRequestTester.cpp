#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "IDataService.hpp"
#include "UserProfile.hpp"

#include "handlers/UserDataRequest.hpp"


TEST_CASE ( "User data request - parametros" ) {
    // Mocks
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    // Test data
    size_t dataLen = 0;
    const char* contentData = nullptr;
    const char* queryString = "Token=123&Nombre=pepe";

    UserDataRequest usReq( *mockService );

    SECTION ( "Seteo de params" ) {
        REQUIRE_NOTHROW ( 
                usReq.LoadParameters( queryString, contentData, dataLen ) 
        );
    }

    SECTION ( "Extracción de params" ) {
        mocker.ExpectCall( mockService, IDataService::IsTokenActive ).With( 123 ).Return( true );
        mocker.ExpectCall( mockService, IDataService::GetUserProfile ).With( 123, "pepe" ).Return( UserProfile() );

        usReq.LoadParameters( queryString, contentData, dataLen );

        // Act
        Response resp = usReq.GetResponseData();

        // Assert
        REQUIRE ( 200 == resp.GetStatus() );
    }

    SECTION ( "Usuario no valido" ) {
        mocker.ExpectCall( mockService, IDataService::IsTokenActive ).Return( false );

        usReq.LoadParameters( queryString, contentData, dataLen );

        // Act
        Response resp = usReq.GetResponseData();

        // Assert
        REQUIRE ( 403 == resp.GetStatus() );
    }

    SECTION ( "Usuario valido" ) {
        mocker.ExpectCall( mockService, IDataService::IsTokenActive ).Return( true );
        mocker.ExpectCall( mockService, IDataService::GetUserProfile ).Return( UserProfile() );

        usReq.LoadParameters( queryString, contentData, dataLen );

        // Act
        Response resp = usReq.GetResponseData();

        // Assert
        REQUIRE ( 200 == resp.GetStatus() );
    }
}


