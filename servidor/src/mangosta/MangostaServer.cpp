#include "MangostaServer.hpp"



MangostaServer::MangostaServer(RequestHandlerFactory fac) 
    : m_keepRunning(false), m_reqFactory(fac)
{
    void* ptrFact = static_cast<void*>( &this->m_reqFactory );

    // Crea el server, le pasa una referencia a la factory y le asigna un puerto para escuchar
    struct mg_server* server = mg_create_server( ptrFact, MangostaServer::EventHandler );
    mg_set_option( server, "listening_port", "8080" );

    this->m_server = server;
}


MangostaServer::~MangostaServer(){
    mg_destroy_server( &this->m_server );
}


void MangostaServer::Start(){
    this->m_keepRunning = true;

    // Corre en un thread el loop de polling del server
    std::thread t( [this]{
        while ( this->m_keepRunning ){
            mg_poll_server( this->m_server, 1000 );
        }
    });

    // Guarda la thread que esta corriendo en el atributo
    std::swap( this->m_runningServerThread, t );
}


void MangostaServer::Stop(){
    // Detiene el loop de polling y espera que termine el server
    this->m_keepRunning = false;
    this->m_runningServerThread.join();
}


//------------------


int MangostaServer::EventHandler( struct mg_connection *conn, enum mg_event evt ){
    RequestHandlerFactory* ptrFactory = static_cast<RequestHandlerFactory*>( conn->server_param );
    
    switch (evt) {
        case MG_AUTH:
            return MG_TRUE;

        case MG_REQUEST:
            {
            // Params del request
            std::string req = conn->request_method; // POST, GET, etc.
            std::string url = conn->uri;
            
            // GET params
            std::string qStr = conn->query_string;  // Lo que viene despues del "?" en la url
            
            // POST data
            char* postData = new char[ conn->content_len ];
            //postData = conn->content; // TODO: Copy the post data
            delete[] postData;

            mg_printf_data( conn, "Hola mundo de los hilos!" ); // Mando la respuesta
            return MG_TRUE;
            }

        default:
            return MG_FALSE;
    }
}


