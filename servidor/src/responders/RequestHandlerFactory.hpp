#ifndef REQUEST_HANDLER_FACTORY_H
#define REQUEST_HANDLER_FACTORY_H

#include <memory>
#include <functional>
#include <unordered_map>

#include "IDataService.hpp"
#include "RequestHandler.hpp"
#include "AuthenticationHandler.hpp"


/**
 * Construye objetos que procesan los distintos pedidos REST del servidor
 * */
class RequestHandlerFactory {
    public:

        /** Constructor de los request handlers.
         *
         * @param[in] service   Referencia a un servicio de almacenamiento de datos.
         * */
        RequestHandlerFactory(IDataService &service);


        virtual ~RequestHandlerFactory();

        
        /** Crea el RequestHandler associado a los parametros dados.
         *
         * @param[in] httpVerb  El tipo de request: GET, POST, etc.
         * @param[in] httpURL   La URL de donde vino el request.
         *
         * @return  Un requestHandler capaz de manejar la operación.
         * */
        std::unique_ptr<RequestHandler> CreateResponder(std::string httpVerb, std::string httpURL) const;


        /** Crea al encargado de validar los accesos a la api REST.
         * Antes de validar el recurso necesita las credenciales, por ese es que pide los parametros del pedido y no el recurso an si.
         *
         * @param[in] queryString  El query string sin el '?' del principio
         * @param[in] data   Los datos binarios del pedido.
         * @param[in] dataLen   La longitud de los datos binarios
         *
         * @return  Un AuthenticationHandler capaz de validar el acceso al recurso pedido.
         * */
        std::unique_ptr<AuthenticationHandler> CreateRequestAuthenticator(const char* queryString, const char* data, size_t dataLen) const;


    private:
        /** Una referencia hacia el servicio de datos.
         * */
        IDataService &m_dataService;


        /** Hace la definición de la factory-map mas clara.
         * */
        typedef std::function< RequestHandler*(IDataService&) > requestCreator;


        /** Contiene todos los elementos a ser creados por la factory.
         * */
        std::unordered_map<std::string, requestCreator> m_factoryMap;

};


#endif

