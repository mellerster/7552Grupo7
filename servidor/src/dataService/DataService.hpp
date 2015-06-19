#ifndef DATASERVICE_H
#define DATASERVICE_H

#include <string>
#include <vector>

#include "IDataService.hpp"
#include "rocaDB/IDB.hpp"
#include "helpers/SessionStateHandler.hpp"
#include "helpers/IPosicionador.hpp"

#include "humblelogging/api.h"



/** Provee la funcionalidad de manejo de datos necesarios para el funcionamiento del servidor web.
 * */
class DataService : public IDataService {
    public:
        DataService(IDB& dbRef, IPosicionador& posInator);
        virtual ~DataService();

        virtual std::vector<UserStatus> ListActiveUsers();
        virtual std::vector<Conversacion> ListActiveConversations(unsigned int token);

        virtual unsigned int StartSession(std::string nombreUsuario, std::string password);
        virtual void EndSession(unsigned int token);

        virtual bool RegisterNewUser(std::string nombreUsuario, std::string password);

        virtual bool IsTokenActive(unsigned int tok);

        virtual UserProfile GetUserProfile(unsigned int token, std::string userID);
        virtual std::string GetCheckinLocations(unsigned int token);

        virtual void ReplaceCheckinLocation(unsigned int token, double latitud, double longitud, std::string fechaHora);
        virtual void ReplaceFoto(unsigned int token, std::string foto);

        virtual void ChangeEstado(unsigned int token, std::string estado);

        virtual unsigned int GetConversacion(unsigned int token, std::string IDdestinatario);
        virtual std::vector<Mensaje> GetMensajes(unsigned int token, unsigned int convID);


    private:

        IDB& m_rocaDB;  /**< Una referencia a la base de datos. */

        IPosicionador& m_posicionador;  /**< Permite acceder al sistema de "checkin". */

        SessionStateHandler m_sessionHandler;   /**< Mantiene la relación entre un token y un user ID. */


        /** Devuelve el primer item que pertenece a ambos vectores.
         * */
        unsigned int GetInterseccion( std::vector<unsigned int> v1, std::vector<unsigned int> v2 );
};


#endif

