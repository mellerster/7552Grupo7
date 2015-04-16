#include "RequestHandlerFactory.hpp"
#include "AuthenticateUserRequest.hpp"
#include "ListUsersRequest.hpp"



RequestHandlerFactory::RequestHandlerFactory(){
}


RequestHandlerFactory::~RequestHandlerFactory(){
}



std::unique_ptr<RequestHandler> RequestHandlerFactory::CreateResponder(std::string httpVerb, std::string httpURL) const{
    std::unique_ptr<RequestHandler> rh( new ListUsersRequest() );

    return rh;
}



