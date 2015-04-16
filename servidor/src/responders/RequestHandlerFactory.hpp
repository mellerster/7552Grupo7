#ifndef REQUEST_HANDLER_FACTORY_H
#define REQUEST_HANDLER_FACTORY_H

#include <memory>
#include "RequestHandler.hpp"


/**
 * Construye objetos que procesan los distintos pedidos REST del servidor
 * */
class RequestHandlerFactory {
    public:
        RequestHandlerFactory();
        virtual ~RequestHandlerFactory();
        
        /**
         * Crea el RequestHandler associado a los parametros dados.
         * @param[in] httpVerb  El tipo de request: GET, POST, etc.
         * @param[in] httpURL   La URL de donde vino el request.
         *
         * @return  Un requestHandler capaz de manejar la operación.
         * */
        std::unique_ptr<RequestHandler> CreateResponder(std::string httpVerb, std::string httpURL) const;

};


#endif

