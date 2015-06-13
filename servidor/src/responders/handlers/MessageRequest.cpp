#include "MessageRequest.hpp"

//#include "dtos/RegistrationDTO.hpp"



MessageRequest::MessageRequest(IDataService &service) : RequestHandler(service) {
}


MessageRequest::~MessageRequest() { }



Response MessageRequest::GetResponseData(){
    // El pedido de pooling es get
    /*
    RegistrationDTO dto( this->m_parsedParameters_QueryString );

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
    Response r(200,"");
    return r;
}


