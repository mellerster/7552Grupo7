#ifndef USER_PROFILE_H
#define USER_PROFILE_H

#include <string>


/**
 * Define los datos que componen el perfil de un usuario.
 * */
class UserProfile {
    public:
        std::string Nombre; /**< El nombre del usuario. */

        std::string Estado; /**< "C" o "D". */

        std::string Foto;   /**< La foto de perfil del usuario. */

        std::string Latitud;    /**< La coordenada de latitud del usuario. */
        std::string Longitud;   /**< La coordenada de longitud del usuario. */
        std::string FechaHora;  /**< La fecha y hora cuando el usuario cargo su ubicación. */

        std::string Ubicacion;  /**< Una descripción del lugar mas cercano a las ultimas coordenadas del usuario. */
};


#endif

