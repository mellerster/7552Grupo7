#include "ConversationRequest.hpp"

#include "dtos/ListaMensajesDTO.hpp"
#include "dtos/MensajeDTO.hpp"



Response ConversationRequest::GetResponseData(){
    // Listado de conversaciones es un request de tipo GET
    ListaMensajesDTO dto( this->m_parsedParameters_QueryString );

    // Chequea que el token sea valido
    if ( !this->m_dataService.IsTokenActive(dto.Token) ){
        return Response( 403, "" );
    }

    // Si no existe ya una conversación crea una nueva
    if (dto.IDConversacion == 0) {
        dto.IDConversacion = this->m_dataService.GetConversacion( dto.Token, dto.IDUsuario );
    }

    ListaMensajesDTO resul;
    resul.IDConversacion = dto.IDConversacion;
    if(dto.IDUsuario.compare("") != 0){
    	resul.IDUsuario = dto.IDUsuario;
    } else {
    	//TODO: Obtener participantes de la conversacion y agregar al participante que no es el del token en el resul
    }

    for ( auto msj : this->m_dataService.GetMensajes(dto.Token, dto.IDConversacion) ) {
        MensajeDTO m;
        m.Mensaje = msj.Texto;
        m.IDRemitente = msj.IDRemitente;
        resul.Mensajes.push_back( m );
    }
    
    // Crea la respuesta
    return Response( 200, resul.ToJSON() );
}
