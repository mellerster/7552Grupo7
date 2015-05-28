#include "CheckinDTO.hpp"



CheckinDTO::CheckinDTO() : BaseDTO(), Token(0), Latitud(""), Longitud(""), Descripcion("") {
}


CheckinDTO::CheckinDTO(Json::Value jData) : BaseDTO(jData), Descripcion("") {
    std::string tok = jData.get("Token", 0).asString();
    this->Token = std::stoul( tok );    // El token es numerico.

    this->Latitud = jData.get("Latitud", "").asString();
    this->Longitud = jData.get("Longitud", "").asString();
    this->Descripcion = jData.get("Descripcion", "").asString();
}


Json::Value CheckinDTO::ToJSON() const {
    Json::Value j = BaseDTO::ToJSON();
    j["Token"] = this->Token;
    j["Latitud"] = this->Latitud;
    j["Longitud"] = this->Longitud;
    j["Descripcion"] = this->Descripcion;

    return j;
}

