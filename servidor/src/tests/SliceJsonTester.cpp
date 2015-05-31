#include "include/catch.hpp"

#include <memory>
#include <string>
#include <sstream>

#include "json/json.h"
#include "rocaDB/RocaDB.hpp"



TEST_CASE ( "JSON to Slice - usando writers" ) {
    Json::Value j;
    j["uno"] = 0;
    j["dos"] = "fish";

    // Escribe el JSON en el stream
    Json::StreamWriterBuilder builder;
    std::unique_ptr<Json::StreamWriter> writer( builder.newStreamWriter() );

    std::stringstream ss;
    writer->write( j, &ss );

    SECTION ( "Usar un bloque de memoria intermedio" ) {
        ss.seekg(0, ss.end);
        size_t tam = ss.tellg();
        ss.seekg(0, ss.beg);

        char* data = new char[ tam ]();

        // Copia los datos al bloque de memoria
        ss.read( data, tam );

        // Del bloque de memoria al Slice
        rocksdb::Slice slMem( data, tam );

        CAPTURE ( slMem.ToString() );

        SECTION ( "Chequear contenido" ) {
            std::string s = slMem.ToString();

            REQUIRE ( std::string::npos != s.find( "uno" ) );
            REQUIRE ( std::string::npos != s.find( "dos" ) );
            REQUIRE ( std::string::npos != s.find( "fish" ) );
        }

        delete[] data;
    }

    SECTION ( "Usando strings" ) {
        std::string s = ss.str();

        rocksdb::Slice slStr = s;

        CAPTURE ( slStr.ToString() );

        SECTION ( "Chequear contenido" ) {
            std::string s = slStr.ToString();

            REQUIRE ( std::string::npos != s.find( "uno" ) );
            REQUIRE ( std::string::npos != s.find( "dos" ) );
            REQUIRE ( std::string::npos != s.find( "fish" ) );
        }
    }

}


TEST_CASE ( "JSON to Slice - usando stream y estilized writer" ) {
    Json::Value j;
    j["uno"] = 0;
    j["dos"] = "fish";

    // Escribe el JSON en el stream
    std::stringstream ss;
    ss << j;

    SECTION ( "Usar un bloque de memoria intermedio" ) {
        ss.seekg(0, ss.end);
        size_t tam = ss.tellg();
        ss.seekg(0, ss.beg);

        char* data = new char[ tam ]();

        // Copia los datos al bloque de memoria
        ss.read( data, tam );

        // Del bloque de memoria al Slice
        rocksdb::Slice slMem( data, tam );

        CAPTURE ( slMem.ToString() );

        SECTION ( "Chequear contenido" ) {
            std::string s = slMem.ToString();

            REQUIRE ( std::string::npos != s.find( "uno" ) );
            REQUIRE ( std::string::npos != s.find( "dos" ) );
            REQUIRE ( std::string::npos != s.find( "fish" ) );
        }

        delete[] data;
    }

    SECTION ( "Usando strings" ) {
        std::string s = ss.str();

        rocksdb::Slice slStr = s;

        CAPTURE ( slStr.ToString() );

        SECTION ( "Chequear contenido" ) {
            std::string s = slStr.ToString();

            REQUIRE ( std::string::npos != s.find( "uno" ) );
            REQUIRE ( std::string::npos != s.find( "dos" ) );
            REQUIRE ( std::string::npos != s.find( "fish" ) );
        }

    }

}


TEST_CASE ( "Slice to JSON" ) {
    rocksdb::Slice sl = "{ \"dos\" : 2,  \"uno\" : \"chips\" }";

    Json::CharReaderBuilder builder;
    std::unique_ptr<Json::CharReader> reader( builder.newCharReader() );

    const char* beg = sl.data();
    const char* end = &beg[ sl.size() ];

    SECTION ( "Chequear exito" ) {
        bool exito = false;
        std::string errs = "";

        REQUIRE_NOTHROW (
            Json::Value jResul;
            exito = reader->parse( beg, end, &jResul, &errs )
        );

        CAPTURE ( errs );
        REQUIRE ( exito );
    }

    SECTION ( "Chequear contenido" ) {
        Json::Value jResul;
        reader->parse( beg, end, &jResul, nullptr );

        int dos = jResul.get("dos", 0).asInt();
        std::string uno = jResul.get("uno", "").asString();

        REQUIRE ( 2 == dos );
        REQUIRE ( "chips" == uno );
    }

}



