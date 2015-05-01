#include "BaseDTO.hpp"
#include <string>



BaseDTO::BaseDTO() : Token(0) {
}


BaseDTO::BaseDTO(Json::Value jData){
    std::string s = jData.get("Token", 0).asString();
    this->Token = std::stoul( s );
}



Json::Value BaseDTO::ToJSON() const{
    Json::Value j;
    j["Token"] = this->Token;

    return j;
}


