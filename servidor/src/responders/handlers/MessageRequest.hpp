#ifndef MESSAGE_REQUEST_H
#define MESSAGE_REQUEST_H

#include "RequestHandler.hpp"
#include "IDataService.hpp"
#include "Response.hpp"



/** Se encarga de responder los pedidos de polling del cliente.
 * */
class MessageRequest : public RequestHandler {
    public:
        MessageRequest(IDataService &service) : RequestHandler(service) { }
        virtual ~MessageRequest() { }
        
        virtual Response GetResponseData();
};


#endif

