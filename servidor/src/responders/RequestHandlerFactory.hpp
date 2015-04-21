#ifndef REQUEST_HANDLER_FACTORY_H
#define REQUEST_HANDLER_FACTORY_H

#include <memory>
#include "RequestHandler.hpp"
#include "IDataService.hpp"
#include "CodecFactory.hpp"


/**
 * Construye objetos que procesan los distintos pedidos REST del servidor
 * */
class RequestHandlerFactory {
    public:

        /** Constructor de los request handlers.
         *
         * @param[in] service   Referencia a un servicio de almacenamiento de datos.
         * @param[in] codecFac  Referencia a una de codificadores y decodificadores de mensajes.
         * */
        RequestHandlerFactory(IDataService &service, CodecFactory codecFac);


        virtual ~RequestHandlerFactory();

        
        /**
         * Crea el RequestHandler associado a los parametros dados.
         * @param[in] httpVerb  El tipo de request: GET, POST, etc.
         * @param[in] httpURL   La URL de donde vino el request.
         *
         * @return  Un requestHandler capaz de manejar la operación.
         * */
        std::unique_ptr<RequestHandler> CreateResponder(std::string httpVerb, std::string httpURL) const;


    protected:
        /**
         * Metodos especializados que crean los distintos tipos de respuestas.
         *
         * @param[in] httpURI   La URI que señala el recurso accedido.
         * */
        RequestHandler* CreateGETResponses(std::string httpURI) const;
        RequestHandler* CreatePUTResponses(std::string httpURI) const;
        RequestHandler* CreatePOSTResponses(std::string httpURI) const;

    private:
        IDataService &m_dataService;
        CodecFactory m_codecFactory;
};


#endif

