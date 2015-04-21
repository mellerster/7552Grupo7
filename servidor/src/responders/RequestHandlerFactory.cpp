#include "RequestHandlerFactory.hpp"

#include "customHandlers/AuthenticateUserRequest.hpp"
#include "customHandlers/ListUsersRequest.hpp"
#include "customHandlers/EmptyRequest.hpp"



RequestHandlerFactory::RequestHandlerFactory(IDataService &service, CodecFactory codecFac)
    : m_dataService(service), m_codecFactory(codecFac)
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
        Codec* codecEmpty = this->m_codecFactory->BuildNotFoundCodec();
        resul = new EmptyRequest(this->m_dataService, codecEmpty);
    }

    std::unique_ptr<RequestHandler> rh( resul );
    return rh;
}


RequestHandler* RequestHandlerFactory::CreateGETResponses(std::string httpURI) const{
    if (httpURI == "/grupo7/api/usuarios"){
        std::unique_ptr<Codec> codecListUsers ( this->m_codecFactory->BuildUsersListingCodec() );
        return new ListUsersRequest(this->m_dataService, codecListUsers);

    } else if (httpURI == ""){
        // TODO
    }

    // Ninguna URI es un match
    return nullptr;
}


RequestHandler* RequestHandlerFactory::CreatePUTResponses(std::string httpURI) const{
    if (httpURI == "/grupo7/api/sesion"){
        std::unique_ptr<Codec> codecAuth ( this->m_codecFactory->BuildAutenticationCodec() );
        return new AuthenticateUserRequest(this->m_dataService, codecAuth);

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


