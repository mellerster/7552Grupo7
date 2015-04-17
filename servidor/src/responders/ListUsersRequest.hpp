#ifndef LIST_USERS_REQUEST_H
#define LIST_USERS_REQUEST_H

#include "RequestHandler.hpp"
#include "IDataService.hpp"
#include "ICodec.hpp"


/**
 * Devuelve la lista de todos los usuarios conectados actualmente.
 * */
class ListUsersRequest : public RequestHandler {
    public:
        ListUsersRequest(IDataService &service, ICodec &codec);
        virtual ~ListUsersRequest();


        virtual std::vector<char> GetResponseData();
};


#endif

