#ifndef ROCA_DATABASE_H
#define ROCA_DATABASE_H

#include <stdexcept>
#include <vector>
#include <string>

#include "IDB.hpp"
#include "json/json.h"
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
        virtual bool AutheticateUser(std::string userID, std::string password);
        virtual bool StoreUserUbicacion(std::string userID, std::string latitud, std::string longitud);
        virtual bool LoadUserUbicacion(std::string userID, std::string &latitud, std::string &longitud);
        virtual bool StoreUserFoto(std::string userID, std::string foto);
        virtual bool LoadUserFoto(std::string userID, std::string &foto);

        virtual unsigned int CreateNewConversacion(std::vector<std::string> listaUsuarios);
        virtual std::vector<unsigned int> GetConversaciones(std::string userID);
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


        /** Dado un Slice, devuelve su contenido en un Json.
         *
         * @returns  Un Json con una copia de los datos originales.
         * */
        Json::Value SliceToJson(rocksdb::Slice s) const;


        /** Dado un Json, devuelve su contenido en un string.
         *
         * Debido a la forma en que los slices funcionan, es necesario guardar una referencia a este string
         * para luego asignarselo a un slice.
         * Esto es porque los slices no tienen una copia de los datos, si no que guardan una referencia a los 
         * datos originales.
         *
         * @returns  Un string con una copia de los datos del Json.
         * */
        std::string JsonToSlice(Json::Value j) const;

};


#endif

