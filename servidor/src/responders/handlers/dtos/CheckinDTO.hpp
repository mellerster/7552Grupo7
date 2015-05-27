#ifndef CHECKIN_DTO_H
#define CHECKIN_DTO_H

#include "json/json.h"
#include "BaseDTO.hpp"



/**
 * Contiene todos los datos necesarios para hacer la consulta de checkin.
 *
 * Se mapea a un JSON de la siguiente forma:
 *
 *      {
 *        Token: 0,
 *        Status: "",
 *        Latitud: "",
 *        Longitud: "",
 *        Descripcion: ""
 *      } 
 * */
class CheckinDTO : public BaseDTO {
    public:
        unsigned int Token;         /**< El token de autenticación del cliente.  */
        std::string Latitud;
        std::string Longitud;
        std::string Descripcion;    /**< La respuesta que contiene la descripción del lugar mas cercano a la coordenada dada. */


        CheckinDTO();        /**< Constructor por defecto */
        CheckinDTO(Json::Value jData);     /**< Inicializa el objeto con los datos del JSON. */

        virtual Json::Value ToJSON() const;     /**< Devuelve un JSON con los datos del objeto. */
};


#endif

