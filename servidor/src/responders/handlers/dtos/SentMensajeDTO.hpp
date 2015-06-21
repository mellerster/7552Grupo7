#ifndef SENT_MENSAJE_H
#define SENT_MENSAJE_H

#include <string>

#include "json/json.h"
#include "BaseDTO.hpp"



/** Define un mensaje posteado.
 *
 * Se mapea a un JSON de la siguiente forma:
 *
 *      {
 *        Status: "",
 *        Token: "",
 *        IDConversacion: "",
 *        Texto: ""
 *      } 
 *
 * */
class SentMensajeDTO : BaseDTO {
    public:
        unsigned int Token;             /**< El token del remitente. */
        unsigned int ConversacionID;    /**< La conversación a la que pertenece el mensaje, */
        std::string Texto;              /**< El texto del mensaje. */


        SentMensajeDTO() : BaseDTO() { }
        SentMensajeDTO(Json::Value jData);

        virtual Json::Value ToJSON() const;
};


#endif

