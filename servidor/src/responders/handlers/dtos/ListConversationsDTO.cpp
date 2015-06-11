#include "ListConversationsDTO.hpp"



ListConversationsDTO::ListConversationsDTO() : BaseDTO(), Token(0) { }


ListConversationsDTO::ListConversationsDTO(Json::Value jData) : BaseDTO(jData) {
    std::string tok = jData.get("Token", 0).asString();
    this->Token = std::stoul( tok );    // El token es numerico.

    // Si la lista de usuarios existe y es un array
    Json::Value lConversaciones = jData["Conversaciones"];
    if ( lConversaciones.type() == Json::ValueType::arrayValue ){

        for (unsigned int i = 0; i < lConversaciones.size(); ++i){
            // Parsea el JSON y lo agrega al vector
            ConversationDTO dto ( lConversaciones[i] );

            this->Conversaciones.push_back( dto );
        }

    }
}


Json::Value ListConversationsDTO::ToJSON() const {
    Json::Value j = BaseDTO::ToJSON();
    j["Token"] = this->Token;

    for (unsigned int i = 0; i < this->Conversaciones.size(); ++i){
        j["Conversaciones"][i] = this->Conversaciones[i].ToJSON();
    }

    return j;
}


