#include "include/catch.hpp"
#include "include/hippomocks.h"

#include <string>

#include "rocaDB/RocaDB.hpp"



TEST_CASE ( "Crear y eliminar la base de datos" ) {
    RocaDB db;

    db.Open("DBTestsStorage.bin");

    SECTION ( "1ra pasada" ) {
        bool existe = db.ExistsUser("pepe");
        bool resul = db.CreateUser("pepe", "123456");

        REQUIRE ( false == existe );
        REQUIRE ( true == resul );
    }

    SECTION ( "2da pasada" ) {
        bool existe = db.ExistsUser("pepe");
        bool resul = db.CreateUser("pepe", "123456");

        REQUIRE ( false == existe );
        REQUIRE ( true == resul );
    }

    db.Close();

    // Destruye la base de datos
    rocksdb::DestroyDB( "DBTestsStorage.bin", rocksdb::Options() );
}


