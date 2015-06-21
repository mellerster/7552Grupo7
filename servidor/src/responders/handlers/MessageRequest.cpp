#include "MessageRequest.hpp"

#include "dtos/ListaMensajesDTO.hpp"
#include "dtos/MensajeDTO.hpp"



Response MessageRequest::GetResponseData(){
    // El pedido de polling es GET
    ListaMensajesDTO dto( this->m_parsedParameters_QueryString );

    if ( !this->m_dataService.IsTokenActive(dto.Token) ){
        return Response( 403, "" );
    }

    ListaMensajesDTO resul;
    resul.IDConversacion = dto.IDConversacion;

    for ( auto mensaje : this->m_dataService.GetMensajesNoLeidos(dto.Token, dto.IDConversacion) ) {
        MensajeDTO m;
        m.Mensaje = mensaje.Texto;
        m.IDRemitente = mensaje.IDRemitente;

        resul.Mensajes.push_back( m );
    }
    
    return Response( 200, resul.ToJSON() );
}


