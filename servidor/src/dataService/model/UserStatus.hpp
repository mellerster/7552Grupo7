#ifndef USER_STATUS_H
#define USER_STATUS_H

#include <string>



/**
 * Define los datos que corresponden al estado de un usuario.
 * */
class UserStatus {
    public:
        std::string Nombre;
        std::string Estado;     /**< Conectado, Desconectado, etc. */

        std::string UltimaActividadHora;
        std::string UltimaActividadFecha;
};


#endif

