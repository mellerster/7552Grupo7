#include "BroadcastHandler.hpp"
#include "dtos/BroadcastDTO.hpp"



BroadcastHandler::BroadcastHandler(IDataService &service) : RequestHandler(service) { }


BroadcastHandler::~BroadcastHandler() { }


Response BroadcastHandler::GetResponseData() {
    // El checkin es un pedido de tipo POST    
    BroadcastDTO pedido( this->m_parsedParameters_ContentData );

    if ( !this->m_dataService.IsTokenActive(pedido.Token) ){
        return Response( 403, "" );
    }
	
    // Envia el mensaje en el dataService
    bool success = this->m_dataService.EnviarBroadcast( pedido.Token, pedido.Mensaje );

    if (success){
        return Response(200, "");

    } else {
        return Response(500, "");
    }
}


