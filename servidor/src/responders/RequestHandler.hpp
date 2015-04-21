#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <memory>
#include <vector>
#include "IDataService.hpp"
#include "Codec.hpp"
#include "Response.hpp"



/**
 * Clase base de todos los objetos capaces de manejar pedidos.
 * */
class RequestHandler {
    public:

        /** Constructor base de los request handlers.
         *
         * @param[in] service   Referencia a un servicio de almacenamiento de datos.
         * @param[in] codec     Referencia a un helper para codificar y decodificar mensajes.
         * */
        RequestHandler(IDataService &service, std::unique_ptr<Codec> codec);


        virtual ~RequestHandler();


        /**
         * Setea los parametros del request.
         *
         * @param[in] queryString   El query string del request sin el "?" del inicio.
         * @param[in] data  Los datos binarios del pedido, suelen ser POST.
         * @param[in] data_len  La cantidad de bytes de datos binarios.
         * */
        void LoadParameters(const char* queryString, const char* data, std::size_t data_len);


        /**
         * Genera la respuesta para ser enviada al cliente.
         *
         * @return  Un contenedor con datos de la respuesta.
         * */
        virtual std::unique_ptr<Response> GetResponseData() = 0;


    protected:
        std::unique_ptr<Codec> m_codec;
        IDataService &m_dataService;
};


#endif

