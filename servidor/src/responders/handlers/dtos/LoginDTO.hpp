#ifndef LOGIN_DTO_H
#define LOGIN_DTO_H

#include "json/json.h"
#include "BaseDTO.hpp"



/**
 * Contiene todos los datos relacionados con los pedidos de login de los clientes.
 *
 * Se mapea a un JSON de la siguiente forma:
 *
 *      {
 *        Token: xxx,
 *        NombreUsuario: "pepe",
 *        Password: "123"
 *      } 
 * */
class LoginDTO : public BaseDTO {
    public:
        std::string NombreUsuario;
        std::string Password;


        LoginDTO();        /**< Constructor por defecto */
        LoginDTO(Json::Value jData);      /**< Inicializa el objeto con los datos del JSON */


        virtual Json::Value ToJSON() const;     /**< Devuelve un JSON con los datos del objeto */

};


#endif

