#ifndef LISTA_MENSAJES_H
#define LISTA_MENSAJES_H

#include <string>
#include <vector>

#include "json/json.h"
#include "BaseDTO.hpp"
#include "MensajeDTO.hpp"



/** Contiene la lista de mensajes pertenecientes a una conversación.
 *
 * Se mapea a un JSON de la siguiente forma:
 *
 *      {
 *        Status: "",
 *        Token: "",
 *        IDConversacion: "",
 *        IDUsuario: "",
 *        Mensajes: [
 *                    <MensajeDTO>,
 *                    <MensajeDTO>,
 *                    ...
 *                  ]
 *      } 
 *
 * */
class ListaMensajesDTO : BaseDTO {
    public:
        unsigned int Token;             /**< Token del usuario. */
        unsigned int IDConversacion;    /**< ID de la conversación de la cual se desean los mensajes. */

        std::string IDUsuario;

        std::vector<MensajeDTO> Mensajes;   /**< Lista con todos los mensajes de una conversación. */


        ListaMensajesDTO() : BaseDTO() { }
        ListaMensajesDTO(Json::Value jData);

        virtual Json::Value ToJSON() const;
};


#endif

