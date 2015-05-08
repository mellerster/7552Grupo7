#include "BaseDTO.hpp"
#include <string>



BaseDTO::BaseDTO() : Status("OK") {
}


BaseDTO::BaseDTO(Json::Value jData){
    this->Status = jData.get("Status", "OK").asString();
}



Json::Value BaseDTO::ToJSON() const{
    Json::Value j;
    j["Status"] = this->Status;

    return j;
}


