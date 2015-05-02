#include "AuthenticationHandler.hpp"



AuthenticationHandler::AuthenticationHandler(IDataService &service) : m_dataService(service)
{
}


AuthenticationHandler::~AuthenticationHandler(){ }



void AuthenticationHandler::LoadParameters(const char*, const char*, size_t){
    // TODO: Parsear los params
}


bool AuthenticationHandler::IsResourceAccesible(std::string httpVerb, std::string httpURI){
    // TODO: Validar que el token este activo para todos los recursos, excepto el login.
    return true;
}


