#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "IDataService.hpp"

#include "handlers/EditPerfilHandler.hpp"


TEST_CASE ( "EditPerfil handler" ) {
    // Mocks
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    // Params
    const char* queryString = nullptr;
    const char* data = "{ \"Token\" : 99 }";
    size_t dataLen = strlen(data) +1;

    EditPerfilHandler handler( *mockService );

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

    SECTION ( "No hay nada para guardar" ) {
        mocker.ExpectCall( mockService, IDataService::IsTokenActive ).Return( true );
        mocker.NeverCall( mockService, IDataService::ReplaceFoto );
        mocker.NeverCall( mockService, IDataService::ChangeEstado );

        // Act
        handler.LoadParameters( queryString, data, dataLen );
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 200 == resp.GetStatus() );
    }

    SECTION ( "Guardar Foto" ) {
        data = "{ \"Token\" : 99, \"Foto\" : \":-)\" }";
        dataLen = strlen(data) +1;

        mocker.ExpectCall( mockService, IDataService::IsTokenActive ).Return( true );
        mocker.ExpectCall( mockService, IDataService::ReplaceFoto );
        mocker.NeverCall( mockService, IDataService::ChangeEstado );

        // Act
        handler.LoadParameters( queryString, data, dataLen );
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 200 == resp.GetStatus() );
    }

    SECTION ( "Guardar Estado" ) {
        data = "{ \"Token\" : 99, \"Estado\" : \"Con sueño\" }";
        dataLen = strlen(data) +1;

        mocker.ExpectCall( mockService, IDataService::IsTokenActive ).Return( true );
        mocker.ExpectCall( mockService, IDataService::ChangeEstado );
        mocker.NeverCall( mockService, IDataService::ReplaceFoto );

        // Act
        handler.LoadParameters( queryString, data, dataLen );
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 200 == resp.GetStatus() );
    }

    SECTION ( "Chequear todos los datos" ) {
        data = "{ \"Token\" : 99, \"Estado\" : \"uno\", \"Foto\" : \"dos\" }";
        dataLen = strlen(data) +1;

        mocker.ExpectCall( mockService, IDataService::IsTokenActive ).With(99).Return( true );
        mocker.ExpectCall( mockService, IDataService::ReplaceFoto ).With(99, "dos");
        mocker.ExpectCall( mockService, IDataService::ChangeEstado ).With(99, "uno");

        // Act
        handler.LoadParameters( queryString, data, dataLen );
        Response resp = handler.GetResponseData();

        // Assert
        REQUIRE ( 200 == resp.GetStatus() );
    }

}


