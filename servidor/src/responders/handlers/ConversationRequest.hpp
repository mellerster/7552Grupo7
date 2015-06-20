#ifndef CONVERSATION_REQUEST_H
#define CONVERSATION_REQUEST_H

#include "IDataService.hpp"
#include "Response.hpp"
#include "RequestHandler.hpp"



/**
 * Devuelve todos los mensajes de una conversación.
 * */
class ConversationRequest : public RequestHandler {
    public:
        ConversationRequest(IDataService &service) : RequestHandler(service) { }

        virtual ~ConversationRequest() { }


        virtual Response GetResponseData();
};


#endif

