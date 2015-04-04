#include <iostream>
#include "mongoose.h"


using namespace std;


// Handles all the messages that arrive at the server
static int eventHandler( struct mg_connection *conn, enum mg_event evt ){
    switch (evt) {
        case MG_AUTH:
            return MG_TRUE;

        case MG_REQUEST:
            mg_printf_data( conn, "Hola mundo!" );
            return MG_TRUE;

        default:
            return MG_FALSE;
    }
}


int main(int argc, char* argv[]) {
    struct mg_server* server = mg_create_server( NULL, eventHandler );
    mg_set_option( server, "listening_port", "8080" );

    cout << "Server started listening on " << mg_get_option( server, "listening_port" ) << endl;
    cout << "Ctrl+c to exit" << endl;

    while (true){
        mg_poll_server( server, 1000 );
    }

    mg_destroy_server( &server );

    return 0;
}

