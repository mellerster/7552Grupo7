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
	
	//TODO: Manejar Broadcast

    // Crea la respuesta
    Response resp( 201, "");
    return resp;
}


