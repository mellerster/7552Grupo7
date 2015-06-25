#include "LoginRequest.hpp"

#include "dtos/LoginDTO.hpp"



LoginRequest::LoginRequest(IDataService &service) : RequestHandler(service) {
}


LoginRequest::~LoginRequest() { }


Response LoginRequest::GetResponseData(){
    // Authentica Users es un pedido de login
    LoginDTO dto( this->m_parsedParameters_ContentData );

    // Validar si los datos del usuario estan en la BD
    int tok = this->m_dataService.StartSession( dto.NombreUsuario, dto.Password );
    if (tok == 0){
        return Response( 403, "" );
    }

    // Cargar el resultado: El ser validado implica recibir un token de conexion
    LoginDTO resul;
    resul.Token = tok;

    return Response( 200, resul.ToJSON() );
}




