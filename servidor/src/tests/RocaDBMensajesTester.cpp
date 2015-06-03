#include "include/catch.hpp"
#include "include/hippomocks.h"

#include <string>
#include <vector>

#include "rocaDB/RocaDB.hpp"



TEST_CASE ( "Pruebas de conversaciones" ) {
    RocaDB db;
    db.Open("DBTestsConversaciones.bin");

    // Se crean un par de usuarios
    bool res1 = db.CreateUser("Tyrion", "123");
    bool res2 = db.CreateUser("Arya", "456");
    REQUIRE ( res1 );
    REQUIRE ( res2 );

    std::vector<std::string> vUsers;
    vUsers.push_back( "Tyrion" );
    vUsers.push_back( "Arya" );

    SECTION ( "Crear nueva conversacion" ) {
        unsigned int convID = db.CreateNewConversacion( vUsers );

        REQUIRE ( 0 < convID );
    }

    SECTION ( "Nueva conversacion asociada a los usuarios" ) {
        unsigned int convID = db.CreateNewConversacion( vUsers );

        std::vector<unsigned int> vConv1 = db.GetConversaciones( "Tyrion" );
        std::vector<unsigned int> vConv2 = db.GetConversaciones( "Arya" );

        REQUIRE ( vConv1.size() == 1 );
        REQUIRE ( vConv2.size() == 1 );

        REQUIRE ( vConv1[0] == convID );
        REQUIRE ( vConv2[0] == convID );
    }

    db.Close();
    rocksdb::DestroyDB( "DBTestsConversaciones.bin", rocksdb::Options() );
}


TEST_CASE ( "Pruebas de mensaje" ) {
    RocaDB db;
    db.Open("DBTestsMensajes.bin");

    // Se crean un par de usuarios
    std::vector<std::string> vUsers = { "pepe", "pepa" };

    for (std::string user : vUsers) {
        bool exito = db.CreateUser( user, "1234" );
        REQUIRE ( exito );
    }

    // Se crea una conversacion para guardar los mensajes
    unsigned int convID = db.CreateNewConversacion( vUsers );
    REQUIRE ( convID > 0 );

    SECTION ( "Obtiene los ID de mensajes de una conversacion - vacia" ) {
        std::vector<unsigned int> vConvs = db.GetMensajesConversacion( convID );

        REQUIRE ( vConvs.empty() );
    }

    SECTION ( "Agregar mensajes a una conversación" ) {
        unsigned int msgID = db.AgregarMensaje( vUsers[0], convID, "Hola mundo!" );

        REQUIRE ( 0 < msgID );
    }

    SECTION ( "Obtener el texto de un mensaje" ) {
        const std::string msg = "Hola mundo!";
        unsigned int msgID = db.AgregarMensaje( vUsers[0], convID, msg );
        std::string resul = db.GetMensaje( msgID );

        REQUIRE ( msg == resul );
    }

    db.Close();
    rocksdb::DestroyDB( "DBTestsMensajes.bin", rocksdb::Options() );
}


TEST_CASE ( "Recuperar los ultimos mensajes" ) {
    RocaDB db;
    db.Open("DBTestsLasts.bin");

    const unsigned int msgID = 999;
    const unsigned int convID = 1010;

    SECTION ( "No hay ultimo mensaje" ) {
        unsigned int lastMsgID = db.GetIDUltimoMensaje("pepe", convID);

        REQUIRE ( 0 == lastMsgID );
    }

    SECTION ( "Hay ultimo mensaje" ) {
        db.SetIDUltimoMensaje("pepe", convID, msgID);
        unsigned int lastMsgID = db.GetIDUltimoMensaje("pepe", convID);

        REQUIRE ( msgID == lastMsgID );
    }

    db.Close();
    rocksdb::DestroyDB( "DBTestsLasts.bin", rocksdb::Options() );
}



