#include "RequestHandlerFactory.hpp"

#include "handlers/EditPerfilHandler.hpp"
#include "handlers/UserSignUpHandler.hpp"
#include "handlers/ListUsersRequest.hpp"
#include "handlers/UserDataRequest.hpp"
#include "handlers/CheckinHandler.hpp"
#include "handlers/BroadcastHandler.hpp"
#include "handlers/LoginRequest.hpp"
#include "handlers/LogoutRequest.hpp"
#include "handlers/EmptyRequest.hpp"
#include "handlers/ListConversationsRequest.hpp"



RequestHandlerFactory::RequestHandlerFactory(IDataService &service) : m_dataService(service) {
    // Cada request responder tiene una entrada en el mapa-factory
    m_factoryMap["GET /grupo7/api/usuarios"] = [] (IDataService& ds) { return new ListUsersRequest(ds); };
    m_factoryMap["GET /grupo7/api/usuario"] = [] (IDataService& ds) { return new UserDataRequest(ds); };
    m_factoryMap["GET /grupo7/api/conversaciones"] = [] (IDataService& ds) { return new ListConversationsRequest(ds); };

    m_factoryMap["PUT /grupo7/api/sesion"] = [] (IDataService& ds) { return new LoginRequest(ds); };
    m_factoryMap["PUT /grupo7/api/usuarios"] = [] (IDataService& ds) { return new EditPerfilHandler(ds); };
    m_factoryMap["PUT /grupo7/api/logout"] = [] (IDataService& ds) { return new LogoutRequest(ds); };

    m_factoryMap["POST /grupo7/api/usuarios"] = [] (IDataService& ds) { return new UserSignUpHandler(ds); };
    m_factoryMap["POST /grupo7/api/checkin"] = [] (IDataService& ds) { return new CheckinHandler(ds); };
    m_factoryMap["POST /grupo7/api/broadcast"] = [] (IDataService& ds) { return new BroadcastHandler(ds); };    

    // TODO: Agregar los responders faltantes
}


RequestHandlerFactory::~RequestHandlerFactory(){
}


std::unique_ptr<RequestHandler> RequestHandlerFactory::CreateResponder(std::string httpVerb, std::string httpURL) const{
    // Busca si la clave del responder pertenece al factory-map
    std::string responderKey = httpVerb + " " + httpURL;
    auto ptrVal = this->m_factoryMap.find( responderKey );

    RequestHandler* resul = nullptr;

    if ( this->m_factoryMap.end() != ptrVal ){
        // El resquest handler esta definido en el factory-map
        resul = ptrVal->second( this->m_dataService );

    } else {
        // No es ningun mensaje definido
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



