#ifndef BROADCAST_DTO_H
#define BROADCAST_DTO_H

#include "json/json.h"
#include "BaseDTO.hpp"



/**
 * Contiene todos los datos necesarios para hacer la consulta de checkin.
 *
 * Se mapea a un JSON de la siguiente forma:
 *
 *      {
 *        Token: 0,
 *      } 
 * */
class BroadcastDTO : public BaseDTO {
    public:
        unsigned int Token;         /**< El token de autenticación del cliente.  */

        BroadcastDTO();        /**< Constructor por defecto */
        BroadcastDTO(Json::Value jData);     /**< Inicializa el objeto con los datos del JSON. */

        virtual Json::Value ToJSON() const;     /**< Devuelve un JSON con los datos del objeto. */
};


#endif

