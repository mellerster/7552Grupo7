#ifndef LIST_USERS_REQUEST_H
#define LIST_USERS_REQUEST_H

#include "RequestHandler.hpp"
#include "IDataService.hpp"
#include "helpers/ICodec.hpp"


/**
 * Devuelve la lista de todos los usuarios conectados actualmente.
 * */
class ListUsersRequest : public RequestHandler {
    public:
        ListUsersRequest(IDataService &service, std::unique_ptr<Codec> codec);
        virtual ~ListUsersRequest();


        virtual std::unique_ptr<Response> GetResponseData();
};


#endif

