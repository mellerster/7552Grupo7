#include "ConversationDTO.hpp"



ConversationDTO::ConversationDTO() : BaseDTO()
{
}


ConversationDTO::ConversationDTO(Json::Value jData) : BaseDTO(jData) {
    std::string tok = jData.get("Token", 0).asString();
    this->Token = std::stoul( tok );    // El token es numerico.
}


Json::Value ConversationDTO::ToJSON() const {
    Json::Value j = BaseDTO::ToJSON();
    return j;
}


