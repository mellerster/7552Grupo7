#ifndef AUTHENTICATE_REQUEST_H
#define AUTHENTICATE_REQUEST_H


#include "RequestHandler.hpp"
#include "Response.hpp"
#include "IDataService.hpp"



/**
 * Loggea al usuario en el sistema.
 * */
class LoginRequest : public RequestHandler {
    public:
        LoginRequest (IDataService &service);
        virtual ~LoginRequest();


        virtual Response GetResponseData();
};


#endif

