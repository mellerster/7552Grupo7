#include "ListUsersRequest.hpp"

#include "dtos/ListUsersDTO.hpp"



ListUsersRequest::ListUsersRequest(IDataService &service) : RequestHandler(service) {
}


ListUsersRequest::~ListUsersRequest(){
}



const Response ListUsersRequest::GetResponseData(){
    // List users es un pedido GET, solo va a existir m_parsedParameters_QueryString
    ListUsersDTO dto( this->m_parsedParameters_QueryString );

    // TODO: Extraer de la BD la lista de usuarios conectados y sus estados

    // TODO: Cargar en el "resul" el listado de usuarios conectados y sus estados
    ListUsersDTO resul;
    
    // Crea la respuesta
    Response resp( 200, resul.ToJSON() );

    return resp;
}
