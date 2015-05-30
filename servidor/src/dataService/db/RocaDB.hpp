#ifndef ROCA_DATABASE_H
#define ROCA_DATABASE_H

#include <stdexcept>
#include <vector>
#include <string>

#include "IDB.hpp"
#include "rocksdb/db.h"
#include "humblelogging/api.h"



/**
 * Implementación de la base de datos mediante RocksDB.
 * */
class RocaDB : public IDB {
    public:
        RocaDB() : m_rockdb( nullptr ) { }
        virtual ~RocaDB();

        virtual void Open(std::string fileName);
        virtual void Close();

        virtual bool ExistsUser(std::string userID);
        virtual bool CreateUser(std::string userID, std::string password);
        virtual bool StoreUserUbicacion(std::string userID, std::string latitud, std::string longitud);
        virtual bool LoadUserUbicacion(std::string userID, std::string &latitud, std::string &longitud);
        virtual bool StoreUserFoto(std::string userID, std::string foto);
        virtual bool LoadUserFoto(std::string userID, std::string &foto);

        virtual unsigned int CreateNewConversacion(std::vector<std::string> listaUsuarios);
        virtual std::vector<unsigned int> GetMensajesConversacion(unsigned int conversacionID);
        virtual unsigned int AgregarMensaje(std::string userID, unsigned int IDConversacion, std::string texto);
        virtual std::string GetMensaje(unsigned int mensajeID);

        virtual unsigned int GetIDUltimoMensaje(std::string userID, unsigned int conversacionID);
        virtual void SetIDUltimoMensaje(std::string userID, unsigned int conversacionID, unsigned int mensajeID);


    protected:

        /** Dado el Id de un usuario devuelve la clave para acceder a los datos correspondientes.
         * */
        std::string GetUserKey(std::string userID) const;


        /** Dado el Id de una conversación devuelve la clave para acceder a los datos correspondientes.
         * */
        std::string GetConversationKey(unsigned int convID) const;


        /** Dado el Id de un mensaje devuelve la clave para acceder a los datos correspondientes.
         * */
        std::string GetMessageKey(unsigned int msgID) const;


        /** Genera la clave para acceder al ultimo mensaje recibido por el usuario.
         * */
        std::string GetUltimoReciboKey(std::string userID, unsigned int convID) const;


        /** Genera ids unicos en todo el sistema.
         * */
        unsigned int GenerateNewID();


    private:

        rocksdb::DB* m_rockdb;  /**< La base de datos. */

};


#endif

