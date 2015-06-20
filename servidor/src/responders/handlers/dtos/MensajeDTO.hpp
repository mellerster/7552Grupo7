#ifndef MENSAJE_DTO_H
#define MENSAJE_DTO_H

#include <string>

#include "json/json.h"
#include "BaseDTO.hpp"



/** Contiene los datos de un mensaje transmitido.
 *
 * Se mapea a un JSON de la siguiente forma:
 *
 *      {
 *        Status: "",
 *        Mensaje: "",
 *        IDRemitente: ""
 *      } 
 *
 * */
class MensajeDTO : BaseDTO {
    public:
        std::string Mensaje;    /**< El texto del mensaje. */
        
        std::string IDRemitente;   /**< El userID del emisor del mensaje. */


        MensajeDTO() : BaseDTO() { }
        MensajeDTO(Json::Value jData);

        virtual Json::Value ToJSON() const;
};


#endif

