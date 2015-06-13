#ifndef MESSAGE_REQUEST_H
#define MESSAGE_REQUEST_H

#include "RequestHandler.hpp"
#include "IDataService.hpp"
#include "Response.hpp"



/**
 * Clase encargada de realizar la registracion de los usuarios nuevos en el sistema.
 * */
class MessageRequest : public RequestHandler {
    public:
        MessageRequest(IDataService &service);
        virtual ~MessageRequest();
        
        virtual Response GetResponseData();
};


#endif

