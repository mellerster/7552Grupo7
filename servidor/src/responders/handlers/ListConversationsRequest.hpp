#ifndef LIST_CONVERSATIONS_REQUEST_H
#define LIST_CONVERSATIONS_REQUEST_H

#include "IDataService.hpp"
#include "Response.hpp"
#include "RequestHandler.hpp"



/**
 * Devuelve la lista de todos las convesaciones de un usuario.
 * */
class ListConversationsRequest : public RequestHandler {
    public:
        ListConversationsRequest(IDataService &service);
        virtual ~ListConversationsRequest();


        virtual Response GetResponseData();
};


#endif

