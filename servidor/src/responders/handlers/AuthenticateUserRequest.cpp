#include "AuthenticateUserRequest.hpp"

#include "dtos/LoginDTO.hpp"



AuthenticateUserRequest::AuthenticateUserRequest(IDataService &service) : RequestHandler(service) {
}


AuthenticateUserRequest::~AuthenticateUserRequest(){
}


const Response AuthenticateUserRequest::GetResponseData(){
    // Authentica Users es un pedido de login
    LoginDTO dto( this->m_parsedParameters_ContentData );

    // TODO: Validar si los datos del usuario estan en la BD

    // TODO: Cargar el resultado
    LoginDTO resul;

    Response resp( 200, resul.ToJSON() );

    return resp;
}




