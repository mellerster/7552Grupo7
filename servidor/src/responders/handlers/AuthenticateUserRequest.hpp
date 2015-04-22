#ifndef AUTHENTICATE_REQUEST_H
#define AUTHENTICATE_REQUEST_H


#include "RequestHandler.hpp"
#include "Response.hpp"
#include "IDataService.hpp"



/**
 * Loggea al usuario en el sistema.
 * */
class AuthenticateUserRequest : public RequestHandler {
    public:
        AuthenticateUserRequest(IDataService &service);
        virtual ~AuthenticateUserRequest();


        virtual const Response GetResponseData();
};


#endif

