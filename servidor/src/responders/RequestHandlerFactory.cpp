#include "RequestHandlerFactory.hpp"

#include "handlers/ListUsersRequest.hpp"
#include "handlers/LoginRequest.hpp"
#include "handlers/EmptyRequest.hpp"



RequestHandlerFactory::RequestHandlerFactory(IDataService &service) : m_dataService(service) {
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
        resul = new EmptyRequest(this->m_dataService);
    }

    std::unique_ptr<RequestHandler> rh( resul );
    return rh;
}


std::unique_ptr<AuthenticationHandler> RequestHandlerFactory::CreateRequestAuthenticator(const char* queryString, const char* data, size_t dataLen) const {
    std::unique_ptr<AuthenticationHandler> rh( new AuthenticationHandler(this->m_dataService) );
    rh->LoadParameters( queryString, data, dataLen );

    return rh;
}


RequestHandler* RequestHandlerFactory::CreateGETResponses(std::string httpURI) const{
    if (httpURI == "/grupo7/api/usuarios"){
        return new ListUsersRequest(this->m_dataService);

    } else if (httpURI == ""){
        // TODO
    }

    // Ninguna URI es un match
    return nullptr;
}


RequestHandler* RequestHandlerFactory::CreatePUTResponses(std::string httpURI) const{
    if (httpURI == "/grupo7/api/sesion"){
        return new LoginRequest(this->m_dataService);

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


