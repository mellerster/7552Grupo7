#include "UserStatusDTO.hpp"



UserStatusDTO::UserStatusDTO() : BaseDTO(),
    Nombre(""), Estado(""), Foto(""),
    UltimaActividadHora(""), UltimaActividadFecha("")
{
}


UserStatusDTO::UserStatusDTO(Json::Value jData) : BaseDTO(jData) {
    this->Nombre = jData.get("Nombre", "").asString();
    this->Estado = jData.get("Estado", "").asString();
    this->Foto = jData.get("Foto", "").asString();

    std::string tok = jData.get("Token", 0).asString();
    this->Token = std::stoul( tok );    // El token es numerico.

    this->UltimaActividadHora = jData.get("UltimaActividadHora", "").asString();
    this->UltimaActividadFecha = jData.get("UltimaActividadFecha", "").asString();
}


Json::Value UserStatusDTO::ToJSON() const {
    Json::Value j = BaseDTO::ToJSON();
    j["Nombre"] = this->Nombre;
    j["Estado"] = this->Estado;
    j["Foto"] = this->Foto;
    j["UltimaActividadHora"] = this->UltimaActividadHora;
    j["UltimaActividadFecha"] = this->UltimaActividadFecha;
    j["Ubicacion"] = this->Ubicacion;

    return j;
}


