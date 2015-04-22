#ifndef RESPONSE_H
#define RESPONSE_H

#include "json/json.h"



/**
 * Objecto que contiene los datos de las respuestas de los request handler.
 * */
class Response {
    public:
        /**
         * Construye una respuesta para los clientes en base a un JSON.
         *
         * @param[in] statusCode    Un código de estado HTTP.
         * @param[in] jsonData      Los datos a enviar en formato JSON.
         * */
        Response(int statusCode, Json::Value jsonData);
        virtual ~Response();

        
        /**
         *  Devuelve el codigo de estado de la operacion realizada.
         * */
        int GetStatus() const;


        /**
         * Devuelve la respuesta en formato binario.
         * */
        const void* GetData() const;


        /**
         * Devuelve la cantidad de bytes de la respuesta.
         * */
        size_t GetDataLength() const;


    private:
        int m_status;

};


#endif

