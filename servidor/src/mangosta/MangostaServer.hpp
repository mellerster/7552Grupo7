#ifndef MANGOSTA_SERVER_H
#define MANGOSTA_SERVER_H

#include <thread>
#include "mongoose.h"
#include "RequestHandlerFactory.hpp"


/**
 * Un servidor web que corré en su propio thread. 
 * */
class MangostaServer {
    public:
        MangostaServer(RequestHandlerFactory fac);
        virtual ~MangostaServer();

        /**
         * Inicia el servidor. 
         * */
        void Start();

        /**
         * Detiene el servidor. 
         * */
        void Stop();

        
    protected:
        /** Maneja los mensajes que llegan al servidor. **/
        static int EventHandler( struct mg_connection *conn, enum mg_event evt );


    private:
        // No se permite copiar el servidor
        MangostaServer(const MangostaServer& ms);
        MangostaServer& operator=(const MangostaServer& ms);

        bool m_keepRunning;
        struct mg_server* m_server;

        // Mantiene una referencia al thread donde corre el servidor
        std::thread m_runningServerThread;

        // Mantiene una referencia a la factory de request's handlers
        RequestHandlerFactory m_reqFactory;
};


#endif 

