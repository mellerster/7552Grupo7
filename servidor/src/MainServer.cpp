#include <iostream>
#include <string>
#include <sstream>
#include "rocksdb/db.h"
#include "RequestHandlerFactory.hpp"
#include "MangostaServer.hpp"
#include "ICodec.hpp"
#include "IDataService.hpp"


using namespace std;


/**
 *
 * */
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

    // Se injectan los servicios en la factory
    ICodec* cTemp = nullptr;
    IDataService* dsTemp = nullptr;
    RequestHandlerFactory factory(*dsTemp, *cTemp);

    // Se injecta la factory en el server
    MangostaServer ms( factory );

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

