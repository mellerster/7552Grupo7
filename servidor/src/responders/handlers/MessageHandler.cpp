#include "MessageHandler.hpp"

//#include "dtos/RegistrationDTO.hpp"



MessageHandler::MessageHandler(IDataService &service) : RequestHandler(service) {
}


MessageHandler::~MessageHandler() { }



Response MessageHandler::GetResponseData(){
    // El pedido de registracion es POST
    /*
    RegistrationDTO dto( this->m_parsedParameters_ContentData );

    bool success = this->m_dataService.RegisterNewUser( dto.NombreUsuario, dto.Password );
    if (success){
        Response r(201, "");    // Created status code
        return r;
    }

    RegistrationDTO resul;
    resul.Status = "ERR";
    Response r(403, resul.ToJSON());    // Forbidden status code

    return r;
    */
    
    //TODO: Implementar
    Response r(201,"");
    return r;
}


