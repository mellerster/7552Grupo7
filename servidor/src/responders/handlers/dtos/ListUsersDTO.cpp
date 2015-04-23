#include "ListUsersDTO.hpp"



ListUsersDTO::ListUsersDTO() { }


ListUsersDTO::ListUsersDTO(Json::Value jData) {
    this->Token = jData.get("Token", "").asString();
    
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
    Json::Value j;
    j["Token"] = this->Token;

    for (unsigned int i = 0; i < this->Usuarios.size(); ++i){
        j["Usuarios"][i] = this->Usuarios[i].ToJSON();
    }

    return j;
}


