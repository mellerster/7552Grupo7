#ifndef BASE_DTO_H
#define BASE_DTO_H

#include "json/json.h"



/**
 * La clase base que define la interfaz de los DTOs.
 *
 *
 * Se mapea a un JSON de la siguiente forma:
 *
 *      {
 *        Token: xxx,
 *        Status: "OK"
 *      }
 * */
class BaseDTO {
    public:
        unsigned int Token;      /**< El token de autenticación del cliente. */
        std::string Status;      /**< El estado del pedido-respuesta; puede ser "OK" o "ERR". */


        BaseDTO();        /**< Constructor por defecto */
        BaseDTO(Json::Value jData);     /**< Inicializa el objeto con los datos del JSON */

        
        virtual Json::Value ToJSON() const;     /**< Devuelve un JSON con los datos del objeto */

};


#endif

