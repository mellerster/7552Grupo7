#ifndef IDATA_SERVICE_H
#define IDATA_SERVICE_H


#include <string>
#include <vector>

#include "model/UserStatus.hpp"



/** La interfaz que todos los servicios de persistencia de datos deben implementar.
 * */
class IDataService {
    public:

        /** Abre la conexion con la base de datos.
         *
         * @return  "true" si la connexion fue abrierta exitosamente, "false" sino.
         * */
        virtual bool Open() = 0;


        /** Cierra la conexion con la base de datos.
         * */
        virtual void Close() = 0;


        /** Comienza la sesión del usuario si este ya esta registrado en el sistema.
         *
         * Chequea si el nombre de usuario y el password estan en la base de datos; Si lo estan se
         * genera una nueva sesion asociada al usuario, si ya existia una sesion activa se la reemplaza,
         * y devuelve un token que representa esa sesión.
         *
         * Si el nombre de usuario y password NO estan en la base de datos se devuelve un token nulo.
         *
         * @param[in] nombreUsuario   El nombre de usuario del cliente.
         * @param[in] password   El password asociado al nombre de usuario.
         *
         * @returns  Un token que representa la nueva sesión del usuario, "0" si no.
         * */
        virtual int startSession(std::string nombreUsuario, std::string password) = 0;


        /** Devuelve el listado con todos los usuarios conectados al sistema.
         *
         * @returns  Una lista con los datos de los usuarios conectados
         * */
        virtual std::vector<UserStatus> ListActiveUsers() = 0;

};


#endif

