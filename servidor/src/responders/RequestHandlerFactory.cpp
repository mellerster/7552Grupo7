#include "RequestHandlerFactory.hpp"
#include "AuthenticateUserRequest.hpp"
#include "ListUsersRequest.hpp"
#include "EmptyRequest.hpp"



RequestHandlerFactory::RequestHandlerFactory(IDataService &service, ICodec &codec)
    : m_codec(codec), m_dataService(service)
{
}


RequestHandlerFactory::~RequestHandlerFactory(){
}



std::unique_ptr<RequestHandler> RequestHandlerFactory::CreateResponder(std::string httpVerb, std::string httpURL) const{
    EmptyRequest* er = new EmptyRequest(this->m_dataService, this->m_codec);

    std::unique_ptr<RequestHandler> rh( er );

    return rh;
}



