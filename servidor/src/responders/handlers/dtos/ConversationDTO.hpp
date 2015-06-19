#ifndef CONVERSATION_DTO_H
#define CONVERSATION_DTO_H

#include "json/json.h"
#include "BaseDTO.hpp"



/**
 * Contiene los datos de una conversación.
 *
 * Se mapea a un JSON de la siguiente forma:
 *
 *      {
 *        Status: "",
 *        Token: "",
 *        IDConversacion: "",
 *        UltimoMensaje: "",
 *        UltimoMensajeLeido: "",
 *        Participantes: [
 *            "<userID>",
 *            "<userID>"
 *            ]
 *      } 
 *
 * */
class ConversationDTO : public BaseDTO {
    public:

        unsigned int Token;         /**< El token de autenticación del cliente.  */
        unsigned int IDConversacion;    /**< El ID único de la conversación. */

        std::string UltimoMensaje;      /**< El texto del ultimo mensaje que forma parte de la conversación. */
        bool UltimoMensajeLeido;        /**< Indica si el ultimo mensaje de la conversación fue leido. */

        std::vector<std::string> Participantes;  /**< Los UserIDs de los participantes de la conversación. */
        
        ConversationDTO();        /**< Constructor por defecto */
        ConversationDTO(Json::Value jData);     /**< Inicializa el objeto con los datos del JSON */

        virtual Json::Value ToJSON() const;     /**< Devuelve un JSON con todos los datos del objeto */

};


#endif

