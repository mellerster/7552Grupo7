#ifndef LOGIN_DTO_H
#define LOGIN_DTO_H

#include "json/json.h"
#include "BaseDTO.hpp"



/**
 * Contiene todos los datos relacionados con los pedidos de login de los clientes.
 * */
class LoginDTO : public BaseDTO {
    public:
        LoginDTO();
        virtual ~LoginDTO();


        /**
         * Inicializa el objeto con los datos del JSON
         * */
        LoginDTO(Json::Value);


        Json::Value ToJSON() const;

};


#endif

