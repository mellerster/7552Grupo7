#ifndef USER_STATUS_DTO_H
#define USER_STATUS_DTO_H

#include "json/json.h"
#include "BaseDTO.hpp"



/**
 * Contiene los datos de estado de un usuario conectado.
 * */
class UserStatusDTO : public BaseDTO {
    public:
        UserStatusDTO();
        virtual ~UserStatusDTO();


        /**
         * Inicializa el objeto con los datos del JSON
         * */
        UserStatusDTO(Json::Value);


        Json::Value ToJSON() const;
};


#endif

