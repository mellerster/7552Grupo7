#include <iostream>
#include <string>
#include <sstream>
#include "mongoose.h"
#include "json/json.h"
#include "rocksdb/db.h"


using namespace std;


// Crea un Json cualquiera como prueba
string BuildJson(string titulo = "Hola mundo"){
    Json::Value resp;
    
    // Campos normales
    resp["Titulo"] = titulo;
    resp["Emisor"] = "He'man";
    resp["Receptor"] = "Leono";
    resp["token"] = 123456;

    // Se define un arreglo de elementos
    resp["Msgs"][0] = "Esta es";
    resp["Msgs"][1] = "una lista de";
    resp["Msgs"][2] = "mensajes, ";
    resp["Msgs"][3] = "como una conversación";
    resp["Msgs"][4] = "normal.";

    stringstream ss;
    ss << resp;

    return ss.str();
}


// Handles all the messages that arrive at the server
static int eventHandler( struct mg_connection *conn, enum mg_event evt ){
    switch (evt) {
        case MG_AUTH:
            return MG_TRUE;

        case MG_REQUEST:
            {
                // Creo un json y lo meto en un string
                string s = BuildJson("Pruebo crear un Json");
                
                // Mando la respuesta
                mg_printf_data( conn, s.c_str() );
                return MG_TRUE;
            }

        default:
            return MG_FALSE;
    }
}


int main() {
    cout << "Abriendo la base de datos... ";
    rocksdb::DB* db;
    rocksdb::Options opt;
    opt.create_if_missing = true;

    rocksdb::Status st = rocksdb::DB::Open( opt, "testDB.bin", &db );
    cout << st.ToString() << "!" << endl;
    cout << endl;
    
    cout << "Levantando webserver... ";
    struct mg_server* server = mg_create_server( NULL, eventHandler );
    mg_set_option( server, "listening_port", "8080" );
    cout << "OK!" << endl;
    cout << endl;

    cout << "El servidor esta escuchando en el puerto " << mg_get_option( server, "listening_port" ) << endl;
    cout << "Presionar Ctrl + c para salir" << endl;

    while (true){
        mg_poll_server( server, 1000 );
    }

    mg_destroy_server( &server );

    delete db;

    return 0;
}

