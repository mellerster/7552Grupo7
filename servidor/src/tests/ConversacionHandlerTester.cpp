#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "json/json.h"
#include "IDataService.hpp"

#include "Response.hpp"
#include "handlers/ListConversationsRequest.hpp"



TEST_CASE ( "Obtener el listado de conversaciones") {
    // Mocks
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    ListConversationsRequest lur( *mockService );

    const size_t dataLen = 0;
    const char* data = nullptr;
    const char* queryString = "Token=999";
    lur.LoadParameters( queryString, data, dataLen );

    REQUIRE ( false );
}


