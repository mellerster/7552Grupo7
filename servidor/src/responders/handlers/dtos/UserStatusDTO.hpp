#ifndef USER_STATUS_DTO_H
#define USER_STATUS_DTO_H

#include "json/json.h"
#include "BaseDTO.hpp"



/**
 * Contiene los datos de estado de un usuario conectado.
 *
 * Se mapea a un JSON de la siguiente forma:
 *
 *      {
 *        Status: "",
 *        Nombre: "xxx",
 *        Estado: "yyy",
 *        Foto: "<Base64>",
 *        UltimaActividadHora: "23:59",
 *        UltimaActividadFecha: "2015/05/08"
 *      } 
 *
 * */
class UserStatusDTO : public BaseDTO {
    public:
        std::string Nombre;     /**< El nombre del usuario. */
        std::string Estado;     /**< El estado del usuario: Conectado, etc. */
        std::string Foto;       /**< La fotografia codificada en base64. */
        std::string UltimaActividadHora;        /**< La hora de ultima actividad del usuario: En formato de 24hs. */
        std::string UltimaActividadFecha;       /**< La fecha de ultima actividad del usuario; En formato año, mes y dia. */
        std::string Ubicacion;
        unsigned int Token;         /**< El token de autenticación del cliente.  */


        UserStatusDTO();        /**< Constructor por defecto */
        UserStatusDTO(Json::Value jData);     /**< Inicializa el objeto con los datos del JSON */

        virtual Json::Value ToJSON() const;     /**< Devuelve un JSON con todos los datos del objeto */

};


#endif

