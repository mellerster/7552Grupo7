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
    RequestHandler* resul = nullptr;

    if (httpVerb == "GET"){
        resul = CreateGETResponses(httpURL);

    } else if (httpVerb == "POST"){
        resul = CreatePOSTResponses(httpURL);

    } else if (httpVerb == "PUT"){
        resul = CreatePUTResponses(httpURL);
    }

    // No es ningun mensaje existente
    if (resul == nullptr){
        resul = new EmptyRequest(this->m_dataService, this->m_codec);
    }

    std::unique_ptr<RequestHandler> rh( resul );
    return rh;
}


RequestHandler* RequestHandlerFactory::CreateGETResponses(std::string httpURI) const{
    if (httpURI == "/grupo7/api/usuarios"){
        return new ListUsersRequest(this->m_dataService, this->m_codec);

    } else if (httpURI == ""){
        // TODO
    }

    // Ninguna URI es un match
    return nullptr;
}


RequestHandler* RequestHandlerFactory::CreatePUTResponses(std::string httpURI) const{
    if (httpURI == "/grupo7/api/sesion"){
        return new AuthenticateUserRequest(this->m_dataService, this->m_codec);

    } else if (httpURI == ""){
        // TODO
    }

    // Ninguna URI es un match
    return nullptr;
}


RequestHandler* RequestHandlerFactory::CreatePOSTResponses(std::string httpURI) const{
    if (httpURI == ""){
        // TODO

    } else if (httpURI == ""){
        // TODO
    }

    // Ninguna URI es un match
    return nullptr;
}


