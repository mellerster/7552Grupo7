#include "ConversationRequest.hpp"

#include "dtos/ConversationDTO.hpp"



ConversationRequest::ConversationRequest(IDataService &service) : RequestHandler(service) {
}


ConversationRequest::~ConversationRequest(){
}



Response ConversationRequest::GetResponseData(){
    // List users es un pedido GET, solo va a existir m_parsedParameters_QueryString
    ConversationDTO dto( this->m_parsedParameters_QueryString );

    // Chequea que el token sea valido
    if ( !this->m_dataService.IsTokenActive(dto.Token) ){
        Response invalid_resp( 403, "" );
        return invalid_resp;
    }

    ConversationDTO resul;

    //TODO: Llamar al dataservice y obtener la conversacion
    
    // Crea la respuesta
    Response resp( 200, resul.ToJSON() );
    return resp;
}
