#include "ListUsersRequest.hpp"

#include "dtos/ListUsersDTO.hpp"



ListUsersRequest::ListUsersRequest(IDataService &service) : RequestHandler(service) {
}


ListUsersRequest::~ListUsersRequest(){
}



Response ListUsersRequest::GetResponseData(){
    // List users es un pedido GET, solo va a existir m_parsedParameters_QueryString
    ListUsersDTO dto( this->m_parsedParameters_QueryString );

    // TODO: Extraer de la BD la lista de usuarios conectados y sus estados

    // TODO: Cargar en el "resul" el listado de usuarios conectados y sus estados
    ListUsersDTO resul;
    resul.Token = "333";

    for (int i = 0; i < 3; ++i){
        UserStatusDTO us;
        us.Token = i;
        us.Nombre = "pepe";
        us.Estado = "Testing: " + i;
        us.UltimaActividadHora = "11:11 hs";
        us.UltimaActividadFecha = "1816/07/09";

        resul.Usuarios.push_back( us );
    }
    
    // Crea la respuesta
    Response resp( 200, resul.ToJSON() );

    return resp;
}
