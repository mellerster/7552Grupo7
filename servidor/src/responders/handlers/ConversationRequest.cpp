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
        return Response( 403, "" );
    }

    // Si no existe ya una conversación crea una nueva
    if (dto.IDConversacion == 0) {
        // Supongo que la lista de participantes solo tiene dos, primero el del token y segundo el destinatario
        dto.IDConversacion = this->m_dataService.GetConversacion( dto.Token, dto.Participantes.back() );
    }

    // TODO: Cargar los mensajes en el DTO
    ConversationDTO resul;

    /*
    for ( auto msj : this->m_dataService.GetMensajes(dto.Token, dto.IDConversacion) ) {
    }
    */
    
    // Crea la respuesta
    Response resp( 200, resul.ToJSON() );
    return resp;
}
