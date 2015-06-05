#include "LoginRequest.hpp"

#include "dtos/LoginDTO.hpp"



LoginRequest::LoginRequest(IDataService &service) : RequestHandler(service) {
}


LoginRequest::~LoginRequest(){
}


Response LoginRequest::GetResponseData(){
    // Authentica Users es un pedido de login
    LoginDTO dto( this->m_parsedParameters_ContentData );

    // Validar si los datos del usuario estan en la BD
    int tok = this->m_dataService.StartSession( dto.NombreUsuario, dto.Password );
    if (tok == 0){
        Response resp( 403, "Los datos no corresponden a un usuario reqistrado" );
        return resp;
    }

    // Cargar el resultado: El ser validado implica recibir un token de conexion
    LoginDTO resul;
    resul.Token = tok;

    Response resp( 200, resul.ToJSON() );
    return resp;
}




