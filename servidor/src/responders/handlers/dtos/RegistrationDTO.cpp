#include "RegistrationDTO.hpp"


RegistrationDTO::RegistrationDTO() : BaseDTO(), Token(0) {
}


RegistrationDTO::RegistrationDTO(Json::Value jData) : BaseDTO(jData) {
    std::string tok = jData.get("Token", 0).asString();

    this->Token = std::stoul( tok );
    this->NombreUsuario = jData.get("NombreUsuario", "").asString();
    this->Password = jData.get("Password", "").asString();
}


Json::Value RegistrationDTO::ToJSON() const {
    Json::Value j = BaseDTO::ToJSON();
    j["NombreUsuario"] = this->NombreUsuario;
    j["Password"] = this->Password;
    j["Token"] = this->Token;

    return j;
}


