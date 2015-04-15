#include <thread>
#include "mongoose.h"


/**
 * Un servidor web que corré en su propio thread
 * */
class MangostaServer {
    public:
        MangostaServer();
        ~MangostaServer();

        void Start();
        void Stop();
        
    private:
        bool m_keepRunning;
        struct mg_server* m_server;

        // Holds the server's running thread
        std::thread m_runningServerThread;


        // Handles the messages that reach the webserver
        static int EventHandler( struct mg_connection *conn, enum mg_event evt );
};


