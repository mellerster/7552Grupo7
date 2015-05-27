#ifndef PERFIL_DTO_H
#define PERFIL_DTO_H

#include "json/json.h"
#include "BaseDTO.hpp"



/**
 * Contiene los datos relacionados con un pedido de edición de perfil.
 *
 * Esto significa que solo puede utilizarse para reemplazar los datos de un perfil.
 *
 * Se mapea a un JSON de la siguiente forma:
 *
 *      {
 *        Status: "",
 *        Token: 0,
 *        Foto: <base64>,
 *        Estado: "C|D"
 *      } 
 * 
 * */
class PerfilDTO : public BaseDTO {
    public:
        unsigned int Token;     /**< Identifica la sesión autenticada del usuario. */
        std::string Estado;     /**< El estado del usuario: Conectado, etc. */
        std::string Foto;


        PerfilDTO();        /**< Constructor por defecto */
        PerfilDTO(Json::Value jData);     /**< Inicializa el objeto con los datos del JSON */

        virtual Json::Value ToJSON() const;     /**< Devuelve un JSON con todos los datos del objeto */
};


#endif

