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


TEST_CASE ( "Request handler - Parseo de query string" ){
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    // Uso un mock porque es un clase virtual pura
    MockedRequestHandler mReqHand( *mockService );

    SECTION ( "Test parseo de query string simple" ){
        const char* qString = "uno=x";
        mReqHand.LoadParameters(qString, nullptr, 0);

        Json::Value parsed = mReqHand.GetQueryStringJSON();

        INFO ( "El resultado del parseo es: " << parsed );
        REQUIRE ( parsed.type() == Json::ValueType::objectValue );

        REQUIRE ( true == parsed.isMember("uno") );
        REQUIRE ( "x" == parsed.get("uno", "").asString() );
    }

    SECTION ( "Test parseo de query string complejo" ){
        const char* qString = "dos=yy&pepe=feo";
        mReqHand.LoadParameters(qString, nullptr, 0);

        Json::Value parsed = mReqHand.GetQueryStringJSON();

        INFO ( "El resultado del parseo es: " << parsed );
        REQUIRE ( parsed.type() == Json::ValueType::objectValue );

        REQUIRE ( true == parsed.isMember("dos") );
        REQUIRE ( true == parsed.isMember("pepe") );

        REQUIRE ( "yy" == parsed.get("dos", "").asString() );
        REQUIRE ( "feo" == parsed.get("pepe", "lindo").asString() );
    }

}



TEST_CASE ( "Request handler - Parseo de JSON content data" ){
    MockRepository mocker;
    IDataService* mockService = mocker.Mock<IDataService>();

    // Uso un mock porque es un clase virtual pura
    MockedRequestHandler mReqHand( *mockService );

    SECTION ( "Test parseo de content data simple" ){
        const char* data = "{ \"uno\": 1 }";
        size_t tam = strlen( data ) +1; // Null terminator

        mReqHand.LoadParameters(nullptr, data, tam);

        Json::Value parsed = mReqHand.GetContentJSON();

        INFO ( "El resultado del parseo es: " << parsed );
        REQUIRE ( parsed.type() == Json::ValueType::objectValue );

        REQUIRE ( true == parsed.isMember("uno") );
        REQUIRE ( "1" == parsed.get("uno", "99").asString() );
    }

    SECTION ( "Test parseo de content data multiple" ){
        const char* data = "{ \"dos\": 2, \"barry\": \"Flash\" }";
        size_t tam = strlen( data ) +1; // Null terminator

        mReqHand.LoadParameters(nullptr, data, tam);

        Json::Value parsed = mReqHand.GetContentJSON();

        INFO ( "El resultado del parseo es: " << parsed );
        REQUIRE ( parsed.type() == Json::ValueType::objectValue );

        REQUIRE ( true == parsed.isMember("dos") );
        REQUIRE ( true == parsed.isMember("barry") );

        REQUIRE ( "2" == parsed.get("dos", "99").asString() );
        REQUIRE ( "Flash" == parsed.get("barry", "eobardt").asString() );
    }

    SECTION ( "Test parseo de content data complejo" ){
        const char* data = "{ \"tres\": 3, \"bean\": \"stalk\", \"arreglo\": [ 1, 2, 3 ], \"objeto\": { \"clave\": \"valor\" } }";
        size_t tam = strlen( data ) +1; // Null terminator

        mReqHand.LoadParameters(nullptr, data, tam);

        Json::Value parsed = mReqHand.GetContentJSON();

        INFO ( "El resultado del parseo es: " << parsed );
        REQUIRE ( parsed.type() == Json::ValueType::objectValue );

        REQUIRE ( true == parsed.isMember("tres") );
        REQUIRE ( true == parsed.isMember("bean") );
        REQUIRE ( true == parsed.isMember("arreglo") );
        REQUIRE ( true == parsed.isMember("objeto") );

        SECTION ( "Chequear los campos simples" ){
            REQUIRE ( 3 == parsed.get("tres", 99).asInt() );
            REQUIRE ( "stalk" == parsed.get("bean", "Mr.").asString() );
        }

        SECTION ( "Chequear el array" ){
            Json::Value jArray = parsed.get("arreglo", "");

            REQUIRE ( Json::ValueType::arrayValue == jArray.type() );
            REQUIRE ( 3 == jArray.size() );

            REQUIRE ( 1 == jArray[0].asInt() );
            REQUIRE ( 2 == jArray[1].asInt() );
            REQUIRE ( 3 == jArray[2].asInt() );
        }

        SECTION ( "Chequear el objeto" ){
            Json::Value jObj = parsed.get("objeto", "");

            REQUIRE ( Json::ValueType::objectValue == jObj.type() );

            REQUIRE ( true == jObj.isMember("clave") );
            REQUIRE ( "valor" == jObj.get("clave", "de sol").asString() );
        }

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





