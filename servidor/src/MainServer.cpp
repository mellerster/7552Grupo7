#include <iostream>
#include <string>

#include "rocksdb/db.h"
#include "humblelogging/api.h"

#include "RequestHandlerFactory.hpp"
#include "posicionaitor/Posicionador.hpp"
#include "HardCodedDataService.hpp"
#include "MangostaServer.hpp"


using namespace std;


// Crea el logger
HUMBLE_LOGGER( logger, "default" );


/**
 *
 * */
int main() {
    // Inicializa el logger
    auto &fac = humble::logging::Factory::getInstance();
    fac.setDefaultFormatter( new humble::logging::PatternFormatter("%date **%lls** [%tid] %filename:%line -> %m\n") );
    fac.registerAppender( new humble::logging::ConsoleAppender() );
    fac.changeGlobalLogLevel( humble::logging::LogLevel::Info );

    // Loggea de diferentes niveles, en orden
    HL_TRACE(logger, "Nivel de trace");
    HL_DEBUG(logger, "Nivel de debug");
    HL_INFO (logger, "Nivel de información");
    HL_WARN (logger, "Nivel de advertencia");
    HL_ERROR(logger, "Nivel de error");
    HL_FATAL(logger, "Nivel de error fatal");

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
    Posicionador checkinProvider;
    HardCodedDataService hardDS( checkinProvider );
    RequestHandlerFactory factory( hardDS );

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

