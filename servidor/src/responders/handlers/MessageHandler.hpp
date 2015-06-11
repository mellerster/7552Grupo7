#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "RequestHandler.hpp"
#include "IDataService.hpp"
#include "Response.hpp"



/**
 * Clase encargada de realizar la registracion de los usuarios nuevos en el sistema.
 * */
class MessageHandler : public RequestHandler {
    public:
        MessageHandler(IDataService &service);
        virtual ~MessageHandler();
        
        virtual Response GetResponseData();
};


#endif

