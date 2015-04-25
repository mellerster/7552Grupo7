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
}


