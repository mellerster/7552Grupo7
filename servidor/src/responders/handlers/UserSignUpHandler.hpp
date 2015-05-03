#ifndef USER_SIGN_UP_H
#define USER_SIGN_UP_H

#include "RequestHandler.hpp"
#include "IDataService.hpp"
#include "Response.hpp"



/**
 * Clase encargada de realizar la registracion de los usuarios nuevos en el sistema.
 * */
class UserSignUpHandler : public RequestHandler {
    public:
        UserSignUpHandler(IDataService &service);
        virtual ~UserSignUpHandler();
        
        virtual Response GetResponseData();
};


#endif

