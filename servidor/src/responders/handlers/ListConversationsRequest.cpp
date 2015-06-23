#include "ListConversationsRequest.hpp"

#include "dtos/ListConversationsDTO.hpp"
#include "dtos/ConversationDTO.hpp"



ListConversationsRequest::ListConversationsRequest(IDataService &service) : RequestHandler(service) {
}


ListConversationsRequest::~ListConversationsRequest() { }



Response ListConversationsRequest::GetResponseData(){
    // List users es un pedido GET, solo va a existir m_parsedParameters_QueryString
    ListConversationsDTO dto( this->m_parsedParameters_QueryString );

    // Chequea que el token sea valido
    if ( !this->m_dataService.IsTokenActive(dto.Token) ){
        return Response( 403, "" );
    }

    ListConversationsDTO resul;

    // Extrae de la BD la lista de usuarios conectados y sus estados
    for ( auto stat : this->m_dataService.ListActiveConversations(dto.Token) ){
        // Carga el listado de usuarios conectados y sus estados
        ConversationDTO conv;
        conv.IDConversacion = stat.IDConversacion;
        conv.UltimoMensaje = stat.UltimoMensaje;
        conv.UltimoMensajeLeido = stat.UltimoMensajeLeido;
        conv.Participantes = stat.Participantes;

        resul.Conversaciones.push_back( conv );
    }
    
    // Crea la respuesta
    return Response( 200, resul.ToJSON() );
}
