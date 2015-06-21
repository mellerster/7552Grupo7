#include "SentMensajeDTO.hpp"



SentMensajeDTO::SentMensajeDTO(Json::Value jData) : BaseDTO(jData) {
    std::string tok = jData.get("Token", 0).asString();
    std::string idConv = jData.get("IDConversacion", "0").asString();

    // El token y el ID de conversacion son numericos
    this->Token = std::stoul( tok );
    this->ConversacionID = std::stoul( idConv );
    this->Texto = jData.get("Texto", "").asString();
}



Json::Value SentMensajeDTO::ToJSON() const {
    Json::Value j = BaseDTO::ToJSON();
    j["Token"] = this->Token;
    j["Texto"] = this->Texto;
    j["IDUsuario"] = this->ConversacionID;

    return j;
}


