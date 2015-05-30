
#include "include/catch.hpp"
#include "include/hippomocks.h"

#include "rocaDB/RocaDB.hpp"



TEST_CASE ( "Crear y eliminar la base de datos" ) {
    RocaDB db;

    db.Open("pepe.bin");

    bool existe = db.ExistsUser("pepe");
    bool resul = db.CreateUser("pepe", "123456");

    CHECK ( false == existe );
    CHECK ( true == resul );

    db.Close();
}

