#ifndef LIST_USERS_DTO_H
#define LIST_USERS_DTO_H

#include <vector>
#include <string>
#include "json/json.h"
#include "BaseDTO.hpp"
#include "UserStatusDTO.hpp"



/**
 * Contiene todos los datos relacionados con el pedido de listado de usuarios.
 *
 * Se mapea a un JSON de la siguiente forma:
 *
 *      {
 *        Token: "xxx",
 *        Usuarios: [
 *                      <UserStatusDTO>,
 *                      <UserStatusDTO>,
 *                      ...
 *                  ]
 *      } 
 * */
class ListUsersDTO : public BaseDTO {
    public:
        std::string Token;      /**< El token de autenticación del cliente */
        std::vector<UserStatusDTO> Usuarios;        /**< La lista de usuarios conectados */


        ListUsersDTO();        /**< Constructor por defecto */
        ListUsersDTO(Json::Value jData);     /**< Inicializa el objeto con los datos del JSON */


        Json::Value ToJSON() const;     /**< Devuelve un JSON con los datos del objeto */

};


#endif

