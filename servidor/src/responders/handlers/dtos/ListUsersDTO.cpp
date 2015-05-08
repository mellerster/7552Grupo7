#include "ListUsersDTO.hpp"



ListUsersDTO::ListUsersDTO() : BaseDTO(), Token(0) { }


ListUsersDTO::ListUsersDTO(Json::Value jData) : BaseDTO(jData) {
    std::string tok = jData.get("Token", 0).asString();
    this->Token = std::stoul( tok );    // El token es numerico.

    // Si la lista de usuarios existe y es un array
    Json::Value lUsuarios = jData["Usuarios"];
    if ( lUsuarios.type() == Json::ValueType::arrayValue ){

        for (unsigned int i = 0; i < lUsuarios.size(); ++i){
            // Parsea el JSON y lo agrega al vector
            UserStatusDTO dto ( lUsuarios[i] );

            this->Usuarios.push_back( dto );
        }

    }
}


Json::Value ListUsersDTO::ToJSON() const {
    Json::Value j = BaseDTO::ToJSON();
    j["Token"] = this->Token;

    for (unsigned int i = 0; i < this->Usuarios.size(); ++i){
        j["Usuarios"][i] = this->Usuarios[i].ToJSON();
    }

    return j;
}


