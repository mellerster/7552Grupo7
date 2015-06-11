#include "BroadcastDTO.hpp"



BroadcastDTO::BroadcastDTO() : BaseDTO(), Token(0) {
}


BroadcastDTO::BroadcastDTO(Json::Value jData) : BaseDTO(jData) {
    std::string tok = jData.get("Token", 0).asString();
    this->Token = std::stoul( tok );    // El token es numerico.
}


Json::Value BroadcastDTO::ToJSON() const {
    Json::Value j = BaseDTO::ToJSON();
    j["Token"] = this->Token;

    return j;
}

