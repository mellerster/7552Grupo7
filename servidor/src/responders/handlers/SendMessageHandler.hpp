#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "RequestHandler.hpp"
#include "IDataService.hpp"
#include "Response.hpp"



/**
 * Clase encargada de realizar la registracion de los usuarios nuevos en el sistema.
 * */
class SendMessageHandler : public RequestHandler {
    public:
        SendMessageHandler(IDataService &service) : RequestHandler(service) { }
        virtual ~SendMessageHandler() { }
        
        virtual Response GetResponseData();
};


#endif

