#include "SendMessageHandler.hpp"

#include "dtos/ListaMensajesDTO.hpp"
#include "dtos/MensajeDTO.hpp"



SendMessageHandler::SendMessageHandler(IDataService &service) : RequestHandler(service) {
}


SendMessageHandler::~SendMessageHandler() { }



Response SendMessageHandler::GetResponseData(){
    // El pedido de enviar mensaje es POST
    
    ListaMensajesDTO dto( this->m_parsedParameters_ContentData );
    MensajeDTO mensajeDTO( this->m_parsedParameters_ContentData );
    // Chequea que el token sea valido
    if ( !this->m_dataService.IsTokenActive(dto.Token) ){
        Response invalid_resp( 403, "" );
        return invalid_resp;
    }

    // Envia el mensaje en el dataService
    bool success = this->m_dataService.AgregarMensaje( dto.Token, dto.IDConversacion, mensajeDTO.Mensaje );
    if (success){
        Response r(201, "");    // Created status code
        return r;
    }

    Response invalid_resp( 403, "" );
    return invalid_resp;
}


