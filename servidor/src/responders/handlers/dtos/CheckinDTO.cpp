#include "CheckinDTO.hpp"



CheckinDTO::CheckinDTO() : BaseDTO(), Token(0), Latitud("0"), Longitud("0"), Descripcion("") {
}


CheckinDTO::CheckinDTO(Json::Value jData) : BaseDTO(jData), Descripcion("") {
    std::string tok = jData.get("Token", 0).asString();
    this->Token = std::stoul( tok );    // El token es numerico.

    this->Latitud = jData.get("Latitud", "0").asString();
    this->Longitud = jData.get("Longitud", "0").asString();
}


Json::Value CheckinDTO::ToJSON() const {
    Json::Value j = BaseDTO::ToJSON();
    j["Token"] = this->Token;
    j["Descripcion"] = this->Descripcion;

    return j;
}

