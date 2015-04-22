#ifndef LIST_USERS_DTO_H
#define LIST_USERS_DTO_H

#include <vector>
#include "json/json.h"
#include "BaseDTO.hpp"
#include "UserStatusDTO.hpp"



/**
 * Contiene todos los datos relacionados con el pedido de listado de usuarios.
 * */
class ListUsersDTO : public BaseDTO {
    public:
        ListUsersDTO();
        virtual ~ListUsersDTO();


        /**
         * Inicializa el objeto con los datos del JSON
         * */
        ListUsersDTO(Json::Value);


        Json::Value ToJSON() const;


    private:
        std::vector<UserStatusDTO> m_listaEstados;

};


#endif

