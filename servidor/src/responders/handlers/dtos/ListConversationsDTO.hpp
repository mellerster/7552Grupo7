#ifndef LIST_CONVERSATIONS_DTO_H
#define LIST_CONVERSATIONS_DTO_H

#include <vector>
#include <string>
#include "json/json.h"
#include "BaseDTO.hpp"
#include "ConversationDTO.hpp"



/**
 * Contiene todos los datos relacionados con el pedido de listado de usuarios.
 *
 * Se mapea a un JSON de la siguiente forma:
 *
 *      {
 *        Token: 0,
 *        Status: "",
 *        Conversaciones: [
 *                      <ConversationDTO>,
 *                      <ConversationDTO>,
 *                      ...
 *                  ]
 *      } 
 * */
class ListConversationsDTO : public BaseDTO {
    public:
        unsigned int Token;         /**< El token de autenticación del cliente.  */
        std::vector<ConversationDTO> Conversaciones;        /**< La lista de conversaciones. */


        ListConversationsDTO();        /**< Constructor por defecto */
        ListConversationsDTO(Json::Value jData);     /**< Inicializa el objeto con los datos del JSON. */


        virtual Json::Value ToJSON() const;     /**< Devuelve un JSON con los datos del objeto. */

};


#endif

