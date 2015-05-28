#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "IDataService.hpp"

#include "handlers/CheckinHandler.hpp"


TEST_CASE ( "Checkin handler" ) {
    // Mocks
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    // Params
    const char* queryString = nullptr;
    const char* data = "{ \"Token\" : 99, \"Latitud\" : \"123\", \"Longitud\" : \"456\" }";
    size_t dataLen = strlen(data) +1;

    CheckinHandler handler( *mockService );

    SECTION ( "No explota" ) {
        REQUIRE_NOTHROW (
                handler.LoadParameters( queryString, data, dataLen );
        );
    }

    SECTION ( "Token no activo" ) {
        mocker.ExpectCall( mockService, IDataService::IsTokenActive ).Return( false );

        // Act
        handler.LoadParameters( queryString, data, dataLen );
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 403 == resp.GetStatus() );
    }

    SECTION ( "Guarda los datos de checkin" ) {
        mocker.ExpectCall( mockService, IDataService::IsTokenActive ).Return( true );
        mocker.ExpectCall( mockService, IDataService::ReplaceCheckinLocation );
        mocker.ExpectCall( mockService, IDataService::GetCheckinLocations ).Return( "Westeros" );

        // Act
        handler.LoadParameters( queryString, data, dataLen );
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 200 == resp.GetStatus() );
    }

}


