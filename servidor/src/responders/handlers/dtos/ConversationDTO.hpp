#ifndef CONVERSATION_DTO_H
#define CONVERSATION_DTO_H

#include "json/json.h"
#include "BaseDTO.hpp"



/**
 * Contiene los datos de estado de un usuario conectado.
 *
 * Se mapea a un JSON de la siguiente forma:
 *
 *      {
 *        Status: ""
 *      } 
 *
 * */
class ConversationDTO : public BaseDTO {
    public:

	unsigned int Token;         /**< El token de autenticación del cliente.  */

        ConversationDTO();        /**< Constructor por defecto */
        ConversationDTO(Json::Value jData);     /**< Inicializa el objeto con los datos del JSON */

        virtual Json::Value ToJSON() const;     /**< Devuelve un JSON con todos los datos del objeto */

};


#endif

