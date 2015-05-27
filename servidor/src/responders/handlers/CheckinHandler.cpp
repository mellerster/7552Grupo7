#include "CheckinHandler.hpp"



CheckinHandler::CheckinHandler(IDataService &service) : RequestHandler(service) { }


CheckinHandler::~CheckinHandler() { }


Response CheckinHandler::GetResponseData() {
    // TODO: Definir que tipo de pedido es el checkin


    // Crea la respuesta
    Response resp( 500, "TODO" );
    return resp;
}


