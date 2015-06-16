#include "CheckinHandler.hpp"
#include "dtos/CheckinDTO.hpp"
#include <time.h>

CheckinHandler::CheckinHandler(IDataService &service) : RequestHandler(service) { }


CheckinHandler::~CheckinHandler() { }


Response CheckinHandler::GetResponseData() {
    // El checkin es un pedido de tipo POST    
    CheckinDTO pedido( this->m_parsedParameters_ContentData );

    if ( !this->m_dataService.IsTokenActive(pedido.Token) ){
        return Response( 403, "" );
    }

    // Convertir los strings en doubles
    double lat = std::stod(pedido.Latitud);
    double lon = std::stod(pedido.Longitud);

    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d/%m/%y a las %H:%M:%S hs.", &tstruct);
    std::string fechaHora =  buf;

    // Se guarda la nueva ubicación del usuario
    this->m_dataService.ReplaceCheckinLocation(pedido.Token, lat, lon, fechaHora );

    // Se recupera la descripcion de la ubicación mas cercana
    CheckinDTO resul;
    resul.Status = "OK";
    resul.Descripcion = this->m_dataService.GetCheckinLocations(pedido.Token);

    // Crea la respuesta
    return Response( 200, resul.ToJSON() );
}


