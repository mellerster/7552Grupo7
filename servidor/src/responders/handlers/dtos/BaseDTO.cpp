#include "BaseDTO.hpp"
#include <string>



BaseDTO::BaseDTO() : Token(0), Status("OK") {
}


BaseDTO::BaseDTO(Json::Value jData){
    std::string t = jData.get("Token", 0).asString();
    std::string s = jData.get("Status", "OK").asString();

    this->Token = std::stoul( t );  // El token es numérico
    this->Status = s;
}



Json::Value BaseDTO::ToJSON() const{
    Json::Value j;
    j["Token"] = this->Token;
    j["Status"] = this->Status;

    return j;
}


