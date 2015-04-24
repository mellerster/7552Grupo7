#include "UserStatusDTO.hpp"



UserStatusDTO::UserStatusDTO() : BaseDTO(),
    Nombre(""), Estado(""), 
    UltimaActividadHora(""), UltimaActividadFecha("")
{
}


UserStatusDTO::UserStatusDTO(Json::Value jData) : BaseDTO(jData) {
    this->Nombre = jData.get("Nombre", "").asString();
    this->Estado = jData.get("Estado", "").asString();

    this->UltimaActividadHora = jData.get("UltimaActividadHora", "").asString();
    this->UltimaActividadFecha = jData.get("UltimaActividadFecha", "").asString();
}



Json::Value UserStatusDTO::ToJSON() const {
    Json::Value j = BaseDTO::ToJSON();
    j["Nombre"] = this->Nombre;
    j["Estado"] = this->Estado;
    j["UltimaActividadHora"] = this->UltimaActividadHora;
    j["UltimaActividadFecha"] = this->UltimaActividadFecha;

    return j;
}


