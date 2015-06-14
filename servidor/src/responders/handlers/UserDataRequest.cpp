#include "UserDataRequest.hpp"

#include "dtos/UserStatusDTO.hpp"
#include <iostream>


UserDataRequest::UserDataRequest(IDataService &service) : RequestHandler(service) {
}


UserDataRequest::~UserDataRequest(){
}


Response UserDataRequest::GetResponseData(){
    // Es un pedido GET, solo va a existir m_parsedParameters_QueryString
    UserStatusDTO dto( this->m_parsedParameters_QueryString );
	
    // Chequea que el token sea valido
    if ( !this->m_dataService.IsTokenActive(dto.Token) ){
        return Response( 403, "" );
    }
    
    UserProfile up = this->m_dataService.GetUserProfile(dto.Token, dto.Nombre);

    // Carga los datos en un DTO
	UserStatusDTO us;
	us.Nombre = up.Nombre;
	us.Estado = up.Estado;
	us.Foto = up.Foto;
	us.Ubicacion = up.Ubicacion;

	us.UltimaActividadHora = "12:53:25 hs";
	us.UltimaActividadFecha = "13 de mayo de 2015";

    
    // Crea la respuesta
    return Response( 200, us.ToJSON() );
}

