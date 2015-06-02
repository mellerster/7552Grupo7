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


TEST_CASE ( "Crear y chequear usuario" ) {
    RocaDB db;
    db.Open("DBUsers.bin");

    db.CreateUser( "uno", "111" );

    SECTION ( "Chequear que existe" ) {
        bool existe = db.ExistsUser( "uno" );

        REQUIRE ( existe );
    }

    SECTION ( "Chequear que no existe" ) {
        bool existe = db.ExistsUser( "dos" );

        REQUIRE_FALSE ( existe );
    }

    SECTION ( "Chequear password - OK" ) {
        bool correcto = db.AutheticateUser( "uno", "111" );

        REQUIRE ( correcto );
    }

    SECTION ( "Chequear password - fail pass" ) {
        bool correcto = db.AutheticateUser( "uno", "222" );

        REQUIRE_FALSE ( correcto );
    }

    SECTION ( "Chequear password - fail user no existe" ) {
        bool correcto = db.AutheticateUser( "dos", "222" );

        REQUIRE_FALSE ( correcto );
    }

    SECTION ( "Chequear password - fail user" ) {
        db.CreateUser( "tres", "333" );
        bool correcto = db.AutheticateUser( "tres", "111" );

        REQUIRE_FALSE ( correcto );
    }

    db.Close();
    rocksdb::DestroyDB( "DBUsers.bin", rocksdb::Options() );
}


TEST_CASE ( "Guardar y recuperar datos del usuario" ) {
    RocaDB db;
    db.Open("DBUsers.bin");

    db.CreateUser( "uno", "111" );
    db.CreateUser( "dos", "222" );

    SECTION ( "Ubicación" ) {
        db.StoreUserUbicacion( "uno", "123", "456" );

        SECTION ( "Recuperar ubicación" ) {
            std::string lat = "";
            std::string lon = "";
            bool exito = db.LoadUserUbicacion( "uno", lat, lon );

            REQUIRE ( exito );
            REQUIRE ( "123" == lat );
            REQUIRE ( "456" == lon );
        }

        SECTION ( "Recuperar ubicación - no hay ubicación cargada" ) {
            std::string lat = "";
            std::string lon = "";
            bool exito = db.LoadUserUbicacion( "dos", lat, lon );

            REQUIRE ( exito );
            REQUIRE ( lat.empty() );
            REQUIRE ( lon.empty() );
        }

        SECTION ( "Recuperar ubicación - no existe el usuario" ) {
            std::string lat = "";
            std::string lon = "";
            bool exito = db.LoadUserUbicacion( "tres", lat, lon );

            REQUIRE_FALSE ( exito );
            REQUIRE ( lat.empty() );
            REQUIRE ( lon.empty() );
        }
    }

    SECTION ( "Foto" ) {
        db.StoreUserFoto( "uno", ":-)" );

        SECTION ( "Recuperar foto" ) {
            std::string foto = "";
            bool exito = db.LoadUserFoto( "uno", foto );

            REQUIRE ( exito );
            REQUIRE ( ":-)" == foto );
        }

        SECTION ( "Recuperar foto - no hay foto cargada" ) {
            std::string foto = "";
            bool exito = db.LoadUserFoto( "dos", foto );

            REQUIRE ( exito );
            REQUIRE ( foto.empty() );
        }

        SECTION ( "Recuperar foto - no existe el usuario" ) {
            std::string foto = "";
            bool exito = db.LoadUserFoto( "tres", foto );

            REQUIRE_FALSE ( exito );
            REQUIRE ( foto.empty() );
        }
    }

    db.Close();
    rocksdb::DestroyDB( "DBUsers.bin", rocksdb::Options() );
}


