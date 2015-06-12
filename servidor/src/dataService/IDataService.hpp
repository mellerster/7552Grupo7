#ifndef IDATA_SERVICE_H
#define IDATA_SERVICE_H


#include <string>
#include <vector>

#include "UserStatus.hpp"
#include "UserProfile.hpp"



/** La interfaz que todos los servicios de persistencia de datos deben implementar.
 * */
class IDataService {
    public:

        /** Indica si el token esta relacionado con alguna sesión activa.
         *
         * Un token activo es aquel que se encuentra asociado a un usuario conectado al sistema.
         *
         * @param[in] tok   El token a validar
         *
         * @returns  True si el token es valido, false si no.
         * */
        virtual bool IsTokenActive(unsigned int tok) = 0;


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
        virtual unsigned int StartSession(std::string nombreUsuario, std::string password) = 0;


        /** Termina la sesión del usuario al que pertenece el token.
         *
         * Si el token no existe no hace nada.
         *
         * @param[in] token     El token asociado a un usuario.
         * */
        virtual void EndSession(unsigned int token) = 0;


        /** Registra un nuevo usuario en el sistema.
         *
         * Inicializa todos los elementos relacionados con un usuario del sistema.
         * El nombre de usuario debe ser unico ya que es la forma de identificar a cada usuario que pertenece al sistema.
         *
         * @param[in] nombreUsuario   El nombre del usuario, unico para cada usuario.
         * @param[in] password   El password associado al nombre de usuario.
         *
         * @returns  True si se completó la registración en forma exitosa, false si no.
         * */
        virtual bool RegisterNewUser(std::string nombreUsuario, std::string password) = 0;


        /** Devuelve el listado con todos los usuarios conectados al sistema.
         *
         * @returns  Una lista con los datos de los usuarios conectados
         * */
        virtual std::vector<UserStatus> ListActiveUsers() = 0;


        /** Devuelve los datos del usuario dado.
         *
         * @param[in] token     El token asociado al usuario del que se desea obtener los datos.
         *
         * @returns  Los datos que conforman el perfil del usuario.
         * */
        virtual UserProfile GetUserProfile(unsigned int token) = 0;


        /** Devuelve un texto descriptivo del lugar mas cercano al ultimo lugar reportado por el usuario.
         *
         * @param[in] token     El token asociado al usuario del que se desea obtener la ubicación.
         *
         * @returns  Un texto asociado al lugar mas cercano a la ubicacion del usuario.
         * */
        virtual std::string GetCheckinLocations(unsigned int token) = 0;


        /** Reemplaza los datos de la ubicación del usuario.
         *
         * Se identifica al usuario mediante su token.
         *
         * @param[in] token     El token asociado al usuario que se desea modificar.
         * @param[in] latitud
         * @param[in] longitud
         * */
        virtual void ReplaceCheckinLocation(unsigned int token, double latitud, double longitud) = 0;


        /** Reemplaza la foto del perfil del usuario.
         * 
         * Se identifica al usuario mediante su token.
         *
         * @param[in] token El token asociado al usuario que se desea modificar.
         * @param[in] foto  Los datos binarios correspondientes a la foto a reemplazar.
         * */
        virtual void ReplaceFoto(unsigned int token, std::string foto) = 0;


        /** Reemplaza el estado del usuario.
         * 
         * Se identifica al usuario mediante su token.
         *
         * @param[in] token El token asociado al usuario que se desea modificar.
         * @param[in] estado  El nuevo estado asociado al usuario.
         * */
        virtual void ReplaceEstado(unsigned int token, std::string estado) = 0;


        virtual ~IDataService() { } 

};


#endif

