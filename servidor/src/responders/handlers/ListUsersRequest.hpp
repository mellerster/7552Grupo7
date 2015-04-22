#ifndef LIST_USERS_REQUEST_H
#define LIST_USERS_REQUEST_H

#include "IDataService.hpp"
#include "Response.hpp"
#include "RequestHandler.hpp"



/**
 * Devuelve la lista de todos los usuarios conectados actualmente.
 * */
class ListUsersRequest : public RequestHandler {
    public:
        ListUsersRequest(IDataService &service);
        virtual ~ListUsersRequest();


        virtual const Response GetResponseData();
};


#endif

