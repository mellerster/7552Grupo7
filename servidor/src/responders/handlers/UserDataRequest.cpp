#include "UserDataRequest.hpp"

#include "dtos/UserStatusDTO.hpp"
#include <iostream>

UserDataRequest::UserDataRequest(IDataService &service) : RequestHandler(service) {
}


UserDataRequest::~UserDataRequest(){
}



Response UserDataRequest::GetResponseData(){
    // List users es un pedido GET, solo va a existir m_parsedParameters_QueryString
    UserStatusDTO dto( this->m_parsedParameters_QueryString );
	
    // Chequea que el token sea valido
    if ( !this->m_dataService.IsTokenActive(dto.Token) ){
        Response invalid_resp( 403, "" );
        return invalid_resp;
    }
    
    UserProfile up = this->m_dataService.GetUserProfile(dto.Token,dto.Nombre);
	UserStatusDTO us;
	us.Nombre = up.Nombre;
	us.Estado = up.Estado;
	us.Foto = up.Foto;
	us.UltimaActividadHora = "12:53:25";
	us.UltimaActividadFecha = "13/05/2015";

    
    // Crea la respuesta
    Response resp( 200, us.ToJSON() );
    return resp;
}
