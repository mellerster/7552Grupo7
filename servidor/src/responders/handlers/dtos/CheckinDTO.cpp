#include "CheckinDTO.hpp"



CheckinDTO::CheckinDTO() : BaseDTO(), Token(0), Latitud(""), Longitud(""), Descripcion(""),
    Hora(""), Fecha("")
{
}


CheckinDTO::CheckinDTO(Json::Value jData) : BaseDTO(jData), Descripcion("") {
    std::string tok = jData.get("Token", 0).asString();
    this->Token = std::stoul( tok );    // El token es numerico.

    this->Latitud = jData.get("Latitud", "0").asString();
    this->Longitud = jData.get("Longitud", "0").asString();
    this->Descripcion = jData.get("Descripcion", "").asString();

    this->Hora = jData.get("Hora", "").asString();
    this->Fecha = jData.get("Fecha", "").asString();
}


Json::Value CheckinDTO::ToJSON() const {
    Json::Value j = BaseDTO::ToJSON();
    j["Token"] = this->Token;
    j["Latitud"] = this->Latitud;
    j["Longitud"] = this->Longitud;
    j["Descripcion"] = this->Descripcion;

    j["Hora"] = this->Hora;
    j["Fecha"] = this->Fecha;

    return j;
}

