#ifndef USER_DATA_REQUEST_H
#define USER_DATA_REQUEST_H

#include "IDataService.hpp"
#include "Response.hpp"
#include "RequestHandler.hpp"



/**
 * Devuelve la lista de todos los usuarios conectados actualmente.
 * */
class UserDataRequest : public RequestHandler {
    public:
        UserDataRequest(IDataService &service);
        virtual ~UserDataRequest();


        virtual Response GetResponseData();
};


#endif

