#ifndef REGISTRATION_DTO_H
#define REGISTRATION_DTO_H

#include "json/json.h"
#include "BaseDTO.hpp"



/**
 * Contiene los datos necesarios para que un usuario pueda darse de alta.
 *
 * Se mapea a un JSON de la siguiente forma:
 *
 *      {
 *        Token: 0,
 *        Status: "",
 *        NombreUsuario: "pepe",
 *        Password: "123"
 *      } 
 * */
class RegistrationDTO : public BaseDTO {
    public:
        std::string NombreUsuario;
        std::string Password;


        RegistrationDTO();        /**< Constructor por defecto */
        RegistrationDTO(Json::Value jData);      /**< Inicializa el objeto con los datos del JSON */


        virtual Json::Value ToJSON() const;     /**< Devuelve un JSON con los datos del objeto */
};


#endif

