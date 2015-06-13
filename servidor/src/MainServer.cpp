#include <iostream>
#include <string>

#include "humblelogging/api.h"

#include "rocaDB/RocaDB.hpp"
#include "helpers/Posicionador.hpp"
#include "RequestHandlerFactory.hpp"

#include "MangostaServer.hpp"
#include "DataService.hpp"


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

    // Se abre la conexion hacia la base de datos
    RocaDB db;
    db.Open( "serverBinData" );
    HL_INFO( logger, "Se abrió la conexión con la base de datos" );

    // Se injectan los servicios en la factory y la factory en el server
    Posicionador checkinProvider;
    DataService realDS( db, checkinProvider );

    RequestHandlerFactory factory( realDS );
    MangostaServer ms( factory );

    string comando = "";
    while (comando != "X"){
        cout << "\n----------------------" << endl;
        cout << "X -> Para terminar" << endl;
        cout << "Y -> Para iniciar" << endl << endl;
        cout << "Ingrese comando: ";
        cin >> comando;

        if ( comando == "Y" ){
            HL_INFO( logger, "Ejecutar comando: iniciar el servidor" );
            cout << "\nstart!\n\n" << endl;
            ms.Start();

        } else if (comando == "X"){
            HL_INFO( logger, "Ejecutar comando: detener el servidor" );
            cout << "\nStop!\n\n" << endl;
            ms.Stop();
        }

        // Limpia un poco la pantalla
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    }

    // Cierra la base de datos
    db.Close();
    HL_INFO( logger, "Se cerró la conexión con la base de datos" );

    cout << "Cerrando aplicacion" << endl;

    return 0;
}

