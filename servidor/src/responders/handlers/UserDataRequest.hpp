#ifndef USER_DATA_REQUEST_H
#define USER_DATA_REQUEST_H

#include "IDataService.hpp"
#include "Response.hpp"
#include "RequestHandler.hpp"



/**
 * Devuelve los datos (perfil) del usuario pedido.
 * */
class UserDataRequest : public RequestHandler {
    public:
        UserDataRequest(IDataService &service);
        virtual ~UserDataRequest();


        virtual Response GetResponseData();
};


#endif

