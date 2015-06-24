#include "SendMessageHandler.hpp"

#include "dtos/SentMensajeDTO.hpp"



Response SendMessageHandler::GetResponseData(){
    // El pedido de enviar mensaje es POST
    SentMensajeDTO dto( this->m_parsedParameters_ContentData );

    // Chequea que el token sea valido
    if ( !this->m_dataService.IsTokenActive(dto.Token) ){
        return Response( 403, "" );
    }

    // Envia el mensaje en el dataService
    bool success = this->m_dataService.AgregarMensaje( dto.Token, dto.ConversacionID, dto.Texto );

    if (success) {
        return Response(200, "");

    } else {
        return Response(500, "");
    }
}


