#include "ListUsersRequest.hpp"

#include "dtos/ListUsersDTO.hpp"



ListUsersRequest::ListUsersRequest(IDataService &service) : RequestHandler(service) {
}


ListUsersRequest::~ListUsersRequest(){
}



Response ListUsersRequest::GetResponseData(){
    // List users es un pedido GET, solo va a existir m_parsedParameters_QueryString
    ListUsersDTO dto( this->m_parsedParameters_QueryString );

    // Chequea que el token sea valido
    if ( !this->m_dataService.IsTokenActive(dto.Token) ){
        Response invalid_resp( 403, "" );
        return invalid_resp;
    }

    ListUsersDTO resul;

    // Extrae de la BD la lista de usuarios conectados y sus estados
    for ( auto stat : this->m_dataService.ListActiveUsers() ){
        // Carga el listado de usuarios conectados y sus estados
        UserStatusDTO us;
        us.Nombre = stat.Nombre;
        us.Estado = stat.Estado;
        us.Foto = stat.Foto;
        us.UltimaActividadHora = stat.UltimaActividadHora;
        us.UltimaActividadFecha = stat.UltimaActividadFecha;

        resul.Usuarios.push_back( us );
    }
    
    // Crea la respuesta
    Response resp( 200, resul.ToJSON() );
    return resp;
}
