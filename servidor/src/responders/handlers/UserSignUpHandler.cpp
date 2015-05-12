#include "UserSignUpHandler.hpp"

#include "dtos/RegistrationDTO.hpp"



UserSignUpHandler::UserSignUpHandler(IDataService &service) : RequestHandler(service) {
}


UserSignUpHandler::~UserSignUpHandler() { }



Response UserSignUpHandler::GetResponseData(){
    // El pedido de registracion es POST
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
}


