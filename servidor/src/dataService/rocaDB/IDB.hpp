#ifndef I_DATABASE_H
#define I_DATABASE_H

#include <string>
#include <vector>



/**
 * La interfaz de la base de datos.
 * */
class IDB {
    public:
        /** Opens the database contained in the given file.
         *
         * If it does not exists, it creates a new database file.
         * */
        virtual void Open(std::string fileName) = 0;


        /** Closes the database, if it's open.
         * */
        virtual void Close() = 0;


        /** Crea un usuario en la base, si ya existe lo reemplaza.
         *
         * @param[in] userID    El nombre de usuario, unico.
         * @param[in] password   El password del usuario.
         *
         * @returns     True si el usuario fue agregado en forma exitosa, False si no.
         * */
        virtual bool CreateUser(std::string userID, std::string password) = 0;


        /** Guarda la ubicación de un usuario.
         *
         * @param[in] userID    El ID de usuario.
         * @param[in] latitud   La coordenada de latitud.
         * @param[in] longitud   La coordenada de longitud.
         *
         * @returns     True si la operación fue exitosa, false si no.
         * */
        virtual bool StoreUserUbicacion(std::string userID, std::string latitud, std::string longitud) = 0;


        /** Recupera la ubicación de un usuario.
         *
         * @param[in] userID    El ID de usuario.
         * @param[out] latitud   La coordenada de latitud.
         * @param[out] longitud   La coordenada de longitud.
         *
         * @returns     True si la operación fue exitosa, false si no.
         * */
        virtual bool LoadUserUbicacion(std::string userID, std::string &latitud, std::string &longitud) = 0;


        /** Guarda la fotografia de un usuario.
         *
         * @param[in] userID    El ID de usuario.
         * @param[in] foto   La foto en base64.
         *
         * @returns     True si la operación fue exitosa, false si no.
         * */
        virtual bool StoreUserFoto(std::string userID, std::string foto) = 0;


        /** Recupera la fotografia de un usuario.
         *
         * @param[in] userID    El ID de usuario.
         * @param[out] foto   La foto en base64.
         *
         * @returns     True si la operación fue exitosa, false si no.
         * */
        virtual bool LoadUserFoto(std::string userID, std::string &foto) = 0;


        /** Indica si ya existe el nombre de usuario en la base.
         * */
        virtual bool ExistsUser(std::string userID) = 0;


        /** Crea una nueva conversación en la base.
         *
         * @param[in] listaUsuarios     Una lista con los ID de los usuarios participantes en la conversación.
         *
         * @returns     El ID de la nueva conversacion creada, 0 si no pudo crearse.
         * */
        virtual unsigned int CreateNewConversacion(std::vector<std::string> listaUsuarios) = 0;


        /** Chequea que el password corresponda al usuario dado.
         *
         * @param[in] userID    El nombre del usuario a autenticar.
         * @param[in] password  El password usuado para la autenticación.
         *
         * @returns True si el password es igual al password del usuario dado, false si no.
         * */
        virtual bool AutheticateUser(std::string userID, std::string password) = 0;


        /** Devuelve los IDs de todos los mensajes contenidos en la conversación data.
         *
         * @param[in] conversacionID    El ID de la conversación de la cual se quieren los mensajes.
         *
         * @returns     Una lista de todos los mensajes contenidos en la conversación.
         * */
        virtual std::vector<unsigned int> GetMensajesConversacion(unsigned int conversacionID) = 0;


        /** Devuelve el ID del ultimo mensaje recibido por el usuario en la conversación dada.
         *
         * @param[in] userID    El nombre de usuario del que se quiere recuperar el mensaje.
         * @param[in] conversacionID    El ID de la conversación de la cual se quiere el ultimo mensaje.
         *
         * @returns     El ID del ultimo mensaje recibo por el usuario en la conversación.
         * */
        virtual unsigned int GetIDUltimoMensaje(std::string userID, unsigned int conversacionID) = 0;


        /** Setea el mensaje dado como ultimo mensaje recibido.
         *
         * @param[in] userID    El nombre de usuario.
         * @param[in] conversacionID    El ID de la conversación.
         * @param[in] mensajeID    El ID del mensaje que se quiere marcar como ultimo.
         * */
        virtual void SetIDUltimoMensaje(std::string userID, unsigned int conversacionID, unsigned int mensajeID) = 0;


        /** Agrega un nuevo mensaje a una conversación.
         *
         * @param[in] userID    El ID del usuario que emite el mensaje.
         * @param[in] IDConversacion    El ID de la conversación a la que se agregará el mensaje.
         * @param[in] texto     El texto del mensaje.
         *
         * @returns     El ID del nuevo mensaje, 0 si no falló.
         * */
        virtual unsigned int AgregarMensaje(std::string userID, unsigned int IDConversacion, std::string texto) = 0;


        /** Recupera el texto del mensaje dado.
         *
         * @param[in] mensajeID     El ID del mensaje que se desea.
         *
         * @returns     El texto correspondiente al ID dado.
         * */
        virtual std::string GetMensaje(unsigned int mensajeID) = 0;



        virtual ~IDB() { }
};


#endif

