#ifndef AUTHENTICATE_REQUEST_H
#define AUTHENTICATE_REQUEST_H

#include "RequestHandler.hpp"


/**
 * Loggea al usuario en el sistema.
 * */
class AuthenticateUserRequest : public RequestHandler {
    public:
        AuthenticateUserRequest();
        virtual ~AuthenticateUserRequest();


        virtual std::vector<char> GetResponseData();
};


#endif

