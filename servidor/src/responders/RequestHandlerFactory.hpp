#ifndef REQUEST_HANDLER_FACTORY_H
#define REQUEST_HANDLER_FACTORY_H

#include <memory>
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


    protected:

        /** Metodos especializados que crean los distintos tipos de respuestas.
         *
         * @param[in] httpURI   La URI que señala el recurso accedido.
         * */
        RequestHandler* CreateGETResponses(std::string httpURI) const;
        RequestHandler* CreatePUTResponses(std::string httpURI) const;
        RequestHandler* CreatePOSTResponses(std::string httpURI) const;


    private:
        IDataService &m_dataService;

};


#endif

