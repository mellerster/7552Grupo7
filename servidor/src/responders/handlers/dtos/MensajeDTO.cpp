#include "MensajeDTO.hpp"


MensajeDTO::MensajeDTO(Json::Value jData) : BaseDTO(jData) {
    this->Mensaje = jData.get("Mensaje", "").asString();
    this->IDRemitente = jData.get("IDRemitente", "").asString();
}


Json::Value MensajeDTO::ToJSON() const {
    Json::Value j = BaseDTO::ToJSON();
    j["IDRemitente"] = this->IDRemitente;
    j["Mensaje"] = this->Mensaje;

    return j;
}


