#include "PerfilDTO.hpp"



PerfilDTO::PerfilDTO() : BaseDTO(), Token(0), Estado(""), Foto("") {
}


PerfilDTO::PerfilDTO(Json::Value jData) : BaseDTO(jData) {
    std::string tok = jData.get("Token", 0).asString();
    this->Token = std::stoul( tok );    // El token es numerico.

    this->Estado = jData.get("Estado", "").asString();
    this->Foto = jData.get("Foto", "").asString();

}


Json::Value PerfilDTO::ToJSON() const {
    Json::Value j = BaseDTO::ToJSON();
    j["Foto"] = this->Foto;
    j["Estado"] = this->Estado;

    return j;
}


