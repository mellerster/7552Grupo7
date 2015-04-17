#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <string>
#include <vector>
#include "IDataService.hpp"
#include "ICodec.hpp"


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
        RequestHandler(IDataService &service, ICodec &codec);


        virtual ~RequestHandler();


        /**
         * Setea los parametros del request.
         * @param[in] queryString   El query string del request sin el "?" del inicio.
         * @param[in] data  Los datos binarios del pedido, suelen ser POST.
         * @param[in] data_len  La cantidad de bytes de datos binarios.
         * */
        void LoadParameters(std::string queryString, const char* data, size_t data_len);


        /**
         * Genera la respuesta para ser enviada al cliente.
         * @return  Un contenedor con datos binarios.
         * */
        virtual std::vector<char> GetResponseData() = 0;


    protected:
        ICodec &m_codec;
        IDataService &m_dataService;
};


#endif

