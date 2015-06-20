#include "ListaMensajesDTO.hpp"
#include "MensajeDTO.hpp"



ListaMensajesDTO::ListaMensajesDTO(Json::Value jData) : BaseDTO(jData) {
    std::string tok = jData.get("Token", 0).asString();
    std::string idConv = jData.get("IDConversacion", "0").asString();

    // El token y el ID de conversacion son numericos
    this->Token = std::stoul( tok );
    this->IDConversacion = std::stoul( idConv );

    this->IDUsuario = jData.get("IDUsuario", "").asString();

    // Si la lista de mensajes existe y es un array
    Json::Value lmensajes = jData["Mensajes"];
    if ( lmensajes.type() == Json::ValueType::arrayValue ) {

        for (unsigned int i = 0; i < lmensajes.size(); ++i){
            // Parsea el JSON y lo agrega al vector
            MensajeDTO dto ( lmensajes[i] );

            this->Mensajes.push_back( dto );
        }
    }
}


Json::Value ListaMensajesDTO::ToJSON() const {
    Json::Value j = BaseDTO::ToJSON();
    j["Token"] = this->Token;
    j["IDUsuario"] = this->IDUsuario;
    j["IDConversacion"] = this->IDConversacion;

    for (unsigned int i = 0; i < this->Mensajes.size(); ++i) {
        j["Mensajes"][i] = this->Mensajes[i].ToJSON();
    }

    return j;
}


