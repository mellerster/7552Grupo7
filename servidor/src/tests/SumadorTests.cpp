#include "catch.hpp"
#include "Sumador.hpp"


TEST_CASE( "Sumar enteros positivos" ){
    Sumador s;
    int res = s.sumar( 1, 2 );
    REQUIRE( res == 3 );
}


TEST_CASE( "Sumar enteros negativos" ){
    Sumador s;
    int res = s.sumar( 1, -2 );
    REQUIRE( res == -1 );
}


TEST_CASE( "Sumar ceros" ){
    Sumador s;

    SECTION( "Primer elemento es cero" ){
        int res = s.sumar( 0, 5 );
        REQUIRE( res == 5 );
    }

    SECTION( "Segundo elemento es cero" ){
        int res = s.sumar( 9, 0 );
        REQUIRE( res == 9 );
    }

    SECTION( "Ambos elementos son cero" ){
        int res = s.sumar( 0, 0 );
        REQUIRE( res == 0 );
    }
}


