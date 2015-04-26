#include "BaseDTO.hpp"



BaseDTO::BaseDTO() : Token(0) {
}


BaseDTO::BaseDTO(Json::Value jData){
    this->Token = jData.get("Token", 0).asUInt();
}



Json::Value BaseDTO::ToJSON() const{
    Json::Value j;
    j["Token"] = this->Token;

    return j;
}


