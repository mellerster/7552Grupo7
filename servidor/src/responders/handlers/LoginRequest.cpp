#include "LoginRequest.hpp"

#include "dtos/LoginDTO.hpp"



LoginRequest::LoginRequest(IDataService &service) : RequestHandler(service) {
}


LoginRequest::~LoginRequest(){
}


Response LoginRequest::GetResponseData(){
    // Authentica Users es un pedido de login
    LoginDTO dto( this->m_parsedParameters_ContentData );

    // TODO: Validar si los datos del usuario estan en la BD

    // TODO: Cargar el resultado: El ser validado implica recibir un token de conexion
    LoginDTO resul;
    resul.Token = "22";

    Response resp( 200, resul.ToJSON() );

    return resp;
}




