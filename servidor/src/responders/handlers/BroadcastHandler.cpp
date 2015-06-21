#include "BroadcastHandler.hpp"
#include "dtos/BroadcastDTO.hpp"

BroadcastHandler::BroadcastHandler(IDataService &service) : RequestHandler(service) { }


BroadcastHandler::~BroadcastHandler() { }


Response BroadcastHandler::GetResponseData() {
    // El checkin es un pedido de tipo POST    
    BroadcastDTO pedido( this->m_parsedParameters_ContentData );

    if ( !this->m_dataService.IsTokenActive(pedido.Token) ){
        Response invalid_resp( 403, "" );
        return invalid_resp;
    }
	
    // Envia el mensaje en el dataService
    bool success = this->m_dataService.EnviarBroadcast( pedido.Token, pedido.Mensaje );
    if (success){
        Response r(201, "");    // Created status code
        return r;
    }

    Response invalid_resp( 403, "" );
    return invalid_resp;
}


