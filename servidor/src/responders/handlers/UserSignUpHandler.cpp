#include "UserSignUpHandler.hpp"

#include "dtos/RegistrationDTO.hpp"



UserSignUpHandler::UserSignUpHandler(IDataService &service) : RequestHandler(service) {
}


UserSignUpHandler::~UserSignUpHandler() { }



Response UserSignUpHandler::GetResponseData(){
    // El pedido de registracion es POST
    RegistrationDTO dto( this->m_parsedParameters_ContentData );

    Response r(200, "");
    return r;
}


