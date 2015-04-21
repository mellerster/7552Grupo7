#ifndef ICODEC_H
#define ICODEC_H

#include <memory>
#include "Response.hpp"
#include "ResultData.hpp"
#include "RequestData.hpp"



/**
 * Define la interfaz para todos los codificadores-decodificadores.
 * */
class Codec {
    public:
        /**
         * Codifica el mensaje en un objeto para ser consumido por el servidor.
         *
         * @param[in] data  El objeto con los datos a codificar.
         *
         * @returns     Una respuesta con los datos codificados.
         * */
        virtual std::unique_ptr<Response> Codificar(ResultData& data) const = 0;


        /**
         * Decodifica los parametros que vienen del servidor.
         *
         * @param[in] qString   Un query string sin el "?" inicial.
         * @param[in] data      El contendor de los datos del pedido.
         * @param[in] dataLen   La longitud de los datos del pedido.
         *
         * @returns     Un objeto con todos los datos recibidos.
         * */
        virtual std::unique_ptr<RequestData> Decodificar(const char* qString, const char* data, size_t dataLen) const = 0;
};


#endif

