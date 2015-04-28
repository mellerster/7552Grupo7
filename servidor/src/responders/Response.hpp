#ifndef RESPONSE_H
#define RESPONSE_H

#include <sstream>
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
        Response(const Response& r);        /**< Contructor copia */

        Response();
        virtual ~Response();

        
        int GetStatus() const;      /**< Devuelve el codigo de estado de la operacion realizada.  */


        /**
         * Devuelve la respuesta en formato binario.
         * Es el cliente el responsable de liberar la memoria.
         * */
        const char* GetData();

        size_t GetDataLength(); /**< Devuelve la cantidad de bytes de la respuesta. */


    private:
        int m_status;
        std::stringstream m_ssContainer;

};


#endif

