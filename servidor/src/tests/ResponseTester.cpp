#include "include/catch.hpp"

#include "json/json.h"
#include "Response.hpp"



TEST_CASE ( "Response tests - construccion" ){ 
    SECTION ( "Construccion con string vacio" ){
        REQUIRE_NOTHROW (
            Response resp (55, "");
        );
    }

    SECTION ( "Construccion con string " ){
        std::string s = "{ Key: 1234 }";
        REQUIRE_NOTHROW (
            Response resp (66, s);
        );
    }

    SECTION ( "Construccion con JSON vacio" ){
        Json::Value j;

        REQUIRE_NOTHROW (
            Response resp (56, j);
        );
    }

    SECTION ( "Construccion con JSON" ){
        Json::Value j;
        j["Token"] = 58;

        REQUIRE_NOTHROW (
            Response resp (57, j);
        );
    }

    SECTION ( "Construccion con JSON complejo" ){
        Json::Value j2;
        j2["Uno"] = 1;
        j2["dos"] = "22";

        Json::Value j;
        j["Token"] = 58;
        j["arreglo"][0] = "A";
        j["arreglo"][1] = "B";
        j["arreglo"][2] = "C";
        j["arreglo"][3] = "D";
        j["obj"] = j2;

        REQUIRE_NOTHROW (
            Response resp (57, j);
        );
    }
}


TEST_CASE ( "Response tests" ){ 
    Json::Value jData;
    jData["uno"] = 2;
    Response resp( 200, jData );


    SECTION ( "Retrieve status code" ){
        int stat = resp.GetStatus();

        REQUIRE ( stat == 200 );
    }

    SECTION ( "Retrieve data size" ){
        size_t tam = resp.GetDataLength();

        REQUIRE ( tam > 0 );
    }

    SECTION ( "Retrieve data" ){
        const char* data = resp.GetData();
        std::string s(data);    // Es mas facil trabajar con strings

        // El json empieza y termina con llaves
        REQUIRE ( false == s.empty() );
        REQUIRE ( '{' == s.front() );
        REQUIRE ( '}' == s.back() );

        // El json debe contener los datos
        REQUIRE ( std::string::npos != s.find("uno") );
        REQUIRE ( std::string::npos != s.find(':') );
        REQUIRE ( std::string::npos != s.find("2") );

        delete[] data;
    }
}


