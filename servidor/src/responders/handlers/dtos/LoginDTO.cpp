#include "LoginDTO.hpp"



LoginDTO::LoginDTO() : BaseDTO() {
}


LoginDTO::LoginDTO(Json::Value jData) : BaseDTO(jData) {
    this->NombreUsuario = jData.get("NombreUsuario", "").asString();
    this->Password = jData.get("Password", "").asString();
}



Json::Value LoginDTO::ToJSON() const{
    Json::Value j = BaseDTO::ToJSON();
    j["NombreUsuario"] = this->NombreUsuario;
    j["Password"] = this->Password;

    return j;
}



