#ifndef CONVERSATION_REQUEST_H
#define CONVERSATION_REQUEST_H

#include "IDataService.hpp"
#include "Response.hpp"
#include "RequestHandler.hpp"



/**
 * Devuelve la lista de todos las convesaciones de un usuario.
 * */
class ConversationRequest : public RequestHandler {
    public:
        ConversationRequest(IDataService &service);
        virtual ~ConversationRequest();


        virtual Response GetResponseData();
};


#endif

