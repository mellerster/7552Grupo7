#include "LoginDTO.hpp"



LoginDTO::LoginDTO() : BaseDTO(), Token(0) {
}


LoginDTO::LoginDTO(Json::Value jData) : BaseDTO(jData) {
    std::string tok = jData.get("Token", 0).asString();

    this->Token = std::stoul( tok );
    this->NombreUsuario = jData.get("NombreUsuario", "").asString();
    this->Password = jData.get("Password", "").asString();
}



Json::Value LoginDTO::ToJSON() const{
    Json::Value j = BaseDTO::ToJSON();
    j["NombreUsuario"] = this->NombreUsuario;
    j["Password"] = this->Password;
    j["Token"] = this->Token;

    return j;
}



