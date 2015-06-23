#include "ConversationDTO.hpp"



ConversationDTO::ConversationDTO() : BaseDTO() {
}


ConversationDTO::ConversationDTO(Json::Value jData) : BaseDTO(jData) {
    std::string tok = jData.get("Token", 0).asString();
    std::string convID = jData.get("IDConversacion", 0).asString();

    this->Token = std::stoul( tok );    // El token es numerico.
    this->IDConversacion = std::stoul( convID );
    this->UltimoMensaje = jData.get("UltimoMensaje", "").asString();
    this->UltimoMensajeLeido = jData.get("UltimoMensajeLeido", false).asBool();

    Json::Value lUsuarios = jData["Participantes"];
    if ( lUsuarios.type() == Json::ValueType::arrayValue ){

        for (unsigned int i = 0; i < lUsuarios.size(); ++i){
            this->Participantes.push_back( lUsuarios[i].asString() );
        }
    }
}


Json::Value ConversationDTO::ToJSON() const {
    Json::Value j = BaseDTO::ToJSON();
    j["Token"] = this->Token;
    j["IDConversacion"] = this->IDConversacion;
    j["UltimoMensaje"] = this->UltimoMensaje;
    j["UltimoMensajeLeido"] = this->UltimoMensajeLeido;
    for (unsigned int i = 0; i < this->Participantes.size(); ++i){
        j["Participantes"][i] = this->Participantes[i];
    }
    
    return j;
}


