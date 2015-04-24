#include "BaseDTO.hpp"



BaseDTO::BaseDTO() : Token("") {
}


BaseDTO::BaseDTO(Json::Value jData){
    this->Token = jData.get("Token", "").asString();
}



Json::Value BaseDTO::ToJSON() const{
    Json::Value j;
    j["Token"] = this->Token;

    return j;
}


