#include "CheckinHandler.hpp"
#include "dtos/CheckinDTO.hpp"



CheckinHandler::CheckinHandler(IDataService &service) : RequestHandler(service) { }


CheckinHandler::~CheckinHandler() { }


Response CheckinHandler::GetResponseData() {
    // El checkin es un pedido de tipo POST
    CheckinDTO pedido( this->m_parsedParameters_ContentData );

    if ( !this->m_dataService.IsTokenActive(pedido.Token) ){
        Response invalid_resp( 403, "" );
        return invalid_resp;
    }

    // Convertir los strings en doubles
    double lat = std::stod(pedido.Latitud);
    double lon = std::stod(pedido.Longitud);

    // Se guarda la nueva ubicación del usuario
    this->m_dataService.ReplaceCheckinLocation(pedido.Token, lat, lon);

    // Se recupera la descripcion de la ubicación mas cercana
    CheckinDTO resul;
    resul.Status = "OK";
    resul.Descripcion = this->m_dataService.GetCheckinLocations(lat, lon);

    // Crea la respuesta
    Response resp( 200, resul.ToJSON() );
    return resp;
}


