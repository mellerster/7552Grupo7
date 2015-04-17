#ifndef AUTHENTICATE_REQUEST_H
#define AUTHENTICATE_REQUEST_H

#include "RequestHandler.hpp"
#include "IDataService.hpp"
#include "ICodec.hpp"


/**
 * Loggea al usuario en el sistema.
 * */
class AuthenticateUserRequest : public RequestHandler {
    public:
        AuthenticateUserRequest(IDataService &service, ICodec &codec);
        virtual ~AuthenticateUserRequest();


        virtual std::vector<char> GetResponseData();
};


#endif

