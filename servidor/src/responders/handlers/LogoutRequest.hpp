#ifndef LOGOUT_REQUEST_H
#define LOGOUT_REQUEST_H


#include "RequestHandler.hpp"
#include "Response.hpp"
#include "IDataService.hpp"



/**
 * Loggea al usuario en el sistema.
 * */
class LogoutRequest : public RequestHandler {
    public:
        LogoutRequest (IDataService &service);
        virtual ~LogoutRequest();


        virtual Response GetResponseData();
};


#endif

