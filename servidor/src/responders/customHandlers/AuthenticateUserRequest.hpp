#ifndef AUTHENTICATE_REQUEST_H
#define AUTHENTICATE_REQUEST_H

#include <memory>
#include <vector>
#include "RequestHandler.hpp"
#include "IDataService.hpp"
#include "Codec.hpp"


/**
 * Loggea al usuario en el sistema.
 * */
class AuthenticateUserRequest : public RequestHandler {
    public:
        AuthenticateUserRequest(IDataService &service, std::unique_ptr<Codec> codec);
        virtual ~AuthenticateUserRequest();


        virtual std::unique_ptr<Response> GetResponseData();
};


#endif

