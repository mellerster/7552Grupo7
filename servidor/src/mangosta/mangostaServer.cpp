#include "mangostaServer.hpp"



MangostaServer::MangostaServer() : m_keepRunning(false){
    // Crea el server y le asigna un puerto para escuchar
    this->m_server = mg_create_server( NULL, MangostaServer::EventHandler );
    mg_set_option( this->m_server, "listening_port", "8080" );
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


/**
 * Maneja todos los mensajes que llegan al server
 * */
int MangostaServer::EventHandler( struct mg_connection *conn, enum mg_event evt ){
    switch (evt) {
        case MG_AUTH:
            return MG_TRUE;

        case MG_REQUEST:    // Mando la respuesta
            mg_printf_data( conn, "Hola mundo de los hilos!" );
            return MG_TRUE;

        default:
            return MG_FALSE;
    }
}


