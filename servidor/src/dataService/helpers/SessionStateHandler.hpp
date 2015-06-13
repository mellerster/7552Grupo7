#ifndef SESSION_STATE_HANDLER_H
#define SESSION_STATE_HANDLER_H

#include <unordered_map>
#include <vector>
#include <utility>
#include <string>



/** Una "Helper-class" para encapsular el manejo de los datos asociados a una sesión.
 * */
class SessionStateHandler {
    public:

        /** Indica si existe una sesión asociada al token.
         *
         * @param[in] token   El token a validar.
         *
         * @returns  True si el token tiene una sesión activa, false si no.
         * */
        bool IsSessionTokenValid(unsigned int token) const;


        /** Inicializa una nueva sesión.
         *
         * @param[in] userID    El ID del usuario asociado a la nueva sesión.
         *
         * @returns  El token de la sesión.
         * */
        unsigned int StartSession(std::string userID);


        /** Termina una sesión.
         *
         * @param[in] token    El token de la sesión a terminar.
         *
         * @returns  True si se borró la sesión, false si esta no existia.
         * */
        bool EndSession(unsigned int token);


        /** Si el usuario tiene una sesión la elimina.
         *
         * @param[in] userID    El ID del usuario asociado a la sesión a borrar.
         *
         * @returns  True si se borró, false si no.
         * */
        bool DeleteUserSession(std::string userID);


        /** Devuelve una lista con los tokens de todas las sesiones.
         * */
        std::vector<unsigned int> GetAllActiveSessionTokens() const;


        /** Devuelve el UserID asociado a una sesión.
         *
         * @param[in] token
         *
         * @returns  El UserID asociado al token.
         * */
        std::string GetAssociatedUserID(unsigned int token) const;


        /** Devuelve el estado de una sesión.
         *
         * @param[in] token
         *
         * @returns  "C" o "D" por "Conectado" y "Desconectado" respectivamente.
         * */
        std::string GetAssociatedUserState(unsigned int token) const;


        /** Devuelve el estado de una sesión.
         *
         * @param[in] userID
         *
         * @returns  "C" o "D" por "Conectado" y "Desconectado" respectivamente.
         * */
        std::string GetAssociatedUserStateByUserID(std::string userID) const;


        /** Cambia el estado asociado al token dado.
         *
         * Los estado validos son "C" y "D", el resto se toman como "C".
         *
         * @param[in] token
         * @param[in] newEstado El nuevo estado asociado al token.
         *
         * @returns  True si se realizó el cambio, false si no.
         * */
        bool SetAssociatedUserState(unsigned int token, std::string newEstado);


    private:

        /** Genera un token único para el usuario dado.
         *
         * @param[in] userID    El ID del usuario.
         *
         * @returns  El token generado.
         * */
        unsigned int GenerateUniqueToken(std::string userID) const;


        /** Un contenedor con los tokens activos.
         * 
         * La clave son los tokens activos.
         * El valor esta compuesto por el userID y el UserState (estado) en ese orden.
         * */
        std::unordered_map<unsigned int, std::pair<std::string, std::string> > m_tokenContainer;
};


#endif

