#include "ListConversationsRequest.hpp"

#include "dtos/ListConversationsDTO.hpp"



ListConversationsRequest::ListConversationsRequest(IDataService &service) : RequestHandler(service) {
}


ListConversationsRequest::~ListConversationsRequest(){
}



Response ListConversationsRequest::GetResponseData(){
    // List users es un pedido GET, solo va a existir m_parsedParameters_QueryString
    ListConversationsDTO dto( this->m_parsedParameters_QueryString );

    // Chequea que el token sea valido
    if ( !this->m_dataService.IsTokenActive(dto.Token) ){
        Response invalid_resp( 403, "" );
        return invalid_resp;
    }

    ListConversationsDTO resul;

    //TODO: Llamar al dataservice y obtener el listado de conversaciones
    
    // Crea la respuesta
    Response resp( 200, resul.ToJSON() );
    return resp;
}
