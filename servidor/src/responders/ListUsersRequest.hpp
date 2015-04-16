#ifndef LIST_USERS_REQUEST_H
#define LIST_USERS_REQUEST_H

#include "RequestHandler.hpp"


/**
 * Devuelve la lista de todos los usuarios conectados actualmente.
 * */
class ListUsersRequest : public RequestHandler {
    public:
        ListUsersRequest();
        virtual ~ListUsersRequest();


        virtual std::vector<char> GetResponseData();
};


#endif

