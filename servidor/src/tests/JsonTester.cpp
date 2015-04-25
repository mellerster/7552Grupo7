#include <string>
#include <string.h>

#include "include/catch.hpp"
#include "include/hippomocks.h"
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


TEST_CASE ( "Descripcion de un JSON vacio" ) {
    Json::Value j("");

    std::string s = j.asString();

    REQUIRE ( s == "" );
}



TEST_CASE ( "Cargar datos crudos en un JSON" ){
    Json::Value j;
    Json::CharReaderBuilder builder;
    Json::CharReader* jcr = builder.newCharReader();

    SECTION ( "Query string a JSON" ){
        const char* qString = "uno=1";
        size_t tam = strlen(qString) +1;
        const char* qStrEnd = &qString[tam];

        std::string errs = "";
        bool resul = jcr->parse( qString, qStrEnd, &j, &errs );

        CAPTURE ( errs );
        REQUIRE ( false == resul ); // No se puede hacer query string a JSON directamente
    }

    SECTION ( "Data block en formato JSON a JSON" ){
        const char* data = "{ \"dos\": 2 }";
        size_t tam = strlen( data ) +1; // Null terminator
        const char* dataEnd = &data[tam];

        std::string errs = "";
        bool resul = jcr->parse( data, dataEnd, &j, &errs );

        CAPTURE ( errs );
        REQUIRE ( true == resul );
    }

    SECTION ( "Data block en formato JSON a JSON v2" ){
        const char* data = "{ \"dos\": 2 }";
        size_t tam = strlen( data ) +1; // Null terminator
        const char* dataEnd = &data[tam];

        std::string errs = "";
        bool resul = jcr->parse( data, dataEnd, &j, &errs );

        REQUIRE ( 2 == j.get("dos", 6).asInt() );
    }

    delete jcr;
}


