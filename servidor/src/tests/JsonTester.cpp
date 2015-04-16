#include <string>
#include "catch.hpp"
#include "json/json.h"


TEST_CASE( "Crear simple json con string", "[json]" ){
    Json::Value j;
    j["uno"] = "Hola";

    SECTION( "Existe el elemento" ){
        Json::ValueType vt = j["uno"].type();
        
        REQUIRE( vt != Json::ValueType::nullValue );
        REQUIRE( vt == Json::ValueType::stringValue );
    }

    SECTION( "El elemento es correcto" ){
        std::string res = j["uno"].asString();
        
        REQUIRE( "Hola" == res );
    }

    SECTION( "No existe el elemento" ){
        Json::ValueType vt = j["dos"].type();
        
        REQUIRE( vt == Json::ValueType::nullValue );
    }
}


TEST_CASE( "Crear simple json con int", "[json]" ){
    Json::Value j;
    j["uno"] = 99;

    SECTION( "Existe el elemento" ){
        Json::ValueType vt = j["uno"].type();
        
        REQUIRE( vt != Json::ValueType::nullValue );
        REQUIRE( vt == Json::ValueType::intValue );
    }

    SECTION( "El elemento es correcto" ){
        int res = j["uno"].asInt();
        
        REQUIRE( 99 == res );
    }
}


TEST_CASE( "Crear simple json con float", "[json]" ){
    Json::Value j;
    j["uno"] = 3.14159f;

    SECTION( "Existe el elemento" ){
        Json::ValueType vt = j["uno"].type();
        
        REQUIRE( vt != Json::ValueType::nullValue );
        REQUIRE( vt == Json::ValueType::realValue );
    }

    SECTION( "El elemento es correcto" ){
        float res = j["uno"].asFloat();
        
        REQUIRE( 3.14159f == res );
    }
}


TEST_CASE( "Crear simple json con array", "[json]" ){
    Json::Value j;
    j["uno"][0] = 1;
    j["uno"][1] = 2;
    j["uno"][2] = 3;
    j["uno"][3] = 4;
    j["uno"][4] = 5;

    SECTION( "Existe el elemento" ){
        Json::ValueType vt = j["uno"].type();
        
        REQUIRE( vt != Json::ValueType::nullValue );
    }

    SECTION( "El elemento es del tipo correcto" ){
        Json::ValueType vt = j["uno"].type();

        REQUIRE( vt == Json::ValueType::arrayValue );
    }

    SECTION( "Tiene la cantidad esperado de elementos" ){
        int cant = j["uno"].size();
        
        REQUIRE( 5 == cant );
    }

    SECTION( "Tiene los elementos correctos en el array" ){
        for (unsigned int i = 0; i < j["uno"].size(); ++i){
            Json::Value temp = j["uno"][i];

            REQUIRE( (i+1) == temp.asInt() );
        }
    }

    SECTION( "Tiene los elementos del tipo correcto en el array" ){
        for (unsigned int i = 0; i < j["uno"].size(); ++i){
            Json::ValueType vt = j["uno"][i].type();

            REQUIRE( vt != Json::ValueType::nullValue );
            REQUIRE( vt == Json::ValueType::intValue );
        }
    }
}



