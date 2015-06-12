#ifndef DATASERVICE_H
#define DATASERVICE_H

#include <string>
#include <vector>
#include <unordered_map>

#include "IDataService.hpp"
#include "rocaDB/IDB.hpp"
#include "posicionaitor/IPosicionador.hpp"

#include "humblelogging/api.h"



/** Provee la funcionalidad de manejo de datos necesarios para el funcionamiento del servidor web.
 * */
class DataService : public IDataService {
    public:
        DataService(IDB& dbRef, IPosicionador& posInator);
        virtual ~DataService();

        virtual std::vector<UserStatus> ListActiveUsers();

        virtual unsigned int StartSession(std::string nombreUsuario, std::string password);
        virtual void EndSession(unsigned int token);

        virtual bool RegisterNewUser(std::string nombreUsuario, std::string password);

        virtual bool IsTokenActive(unsigned int tok);

        virtual UserProfile GetUserProfile(unsigned int token, std::string userID);
        virtual std::string GetCheckinLocations(unsigned int token);

        virtual void ReplaceCheckinLocation(unsigned int token, double latitud, double longitud);
        virtual void ReplaceFoto(unsigned int token, std::string foto);
        virtual void ReplaceEstado(unsigned int token, std::string estado);


    private:

        IDB& m_rocaDB;  /**< Una referencia a la base de datos. */

        IPosicionador& m_posicionador;  /**< Permite acceder al sistema de "checkin". */


        /** Mantiene la relación entre un token y un user ID.
         * */
        std::unordered_map<unsigned int, std::string> m_tokenContainer;


        /** Indica si un usuario tiene una sessión abierta.
         * 
         * Si la tiene devuelve su token, si no "0".
         * */
        unsigned int ExisteSessionUsuario(std::string nombreUsuario) const;
        

        /** Genera un token unico para el usuario dado.
         * */
        unsigned int GenerateTokenUnico(std::string nomUsuario) const;

};


#endif

