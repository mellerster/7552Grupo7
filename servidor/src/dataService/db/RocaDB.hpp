#ifndef ROCA_DATABASE_H
#define ROCA_DATABASE_H

#include "IDB.hpp"
#include "rocksdb/db.h"
#include "humblelogging/api.h"



/**
 * Implementación de la base de datos mediante RocksDB.
 * */
class RocaDB : public IDB {
    public:
        RocaDB();
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

    private:

        rocksdb::DB* m_rockdb;  /**< La base de datos. */
};


#endif

