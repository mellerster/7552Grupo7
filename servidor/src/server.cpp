#include <iostream>
#include <string>
#include <sstream>
#include "mangostaServer.hpp"
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




int main() {
    /*
    cout << "Abriendo la base de datos... ";
    rocksdb::DB* db;
    rocksdb::Options opt;
    opt.create_if_missing = true;

    rocksdb::Status st = rocksdb::DB::Open( opt, "testDB.bin", &db );
    cout << st.ToString() << "!" << endl;
    cout << endl;

    delete db;
    */

    MangostaServer ms;

    string comando = "";
    while (comando != "X"){
        cout << endl << "----------------------" << endl;
        cout << "X -> Para terminar" << endl;
        cout << "Y -> Para iniciar" << endl << endl;
        cout << "Ingrese comando: ";
        cin >> comando;

        if ( comando == "Y" ){
            cout << "start!" << endl;
            ms.Start();

        } else if (comando == "X"){
            cout << "Stop!" << endl;
            ms.Stop();
        }
    }

    cout << "Cerrando aplicacion" << endl;

    return 0;
}

