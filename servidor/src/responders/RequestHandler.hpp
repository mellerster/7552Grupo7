#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include "json/json.h"
#include "IDataService.hpp"
#include "Response.hpp"



/**
 * Clase base de todos los objetos capaces de manejar pedidos.
 * */
class RequestHandler {
    public:

        /** Constructor base de los request handlers.
         *
         * @param[in] service   Referencia a un servicio de almacenamiento de datos.
         * */
        RequestHandler(IDataService &service);


        virtual ~RequestHandler();


        /**
         * Setea los parametros del request.
         *
         * @param[in] queryString   El query string del request sin el "?" del inicio.
         * @param[in] data  Los datos binarios del pedido, suelen ser POST.
         * @param[in] data_len  La cantidad de bytes de datos binarios.
         * */
        void LoadParameters(const char* queryString, const char* data, size_t data_len);


        /**
         * Genera la respuesta para ser enviada al cliente.
         *
         * @return  Un contenedor con datos de la respuesta.
         * */
        virtual Response GetResponseData() = 0;


    protected:
        IDataService &m_dataService;


        /**
         * El JSON correspondiente al 'Content data' esta disponible para las clases derivadas.
         * */
        Json::Value m_parsedParameters_ContentData;


        /**
         * El JSON correspondiente al 'query string' esta disponible para las clases derivadas.
         * */
        Json::Value m_parsedParameters_QueryString;


    private:

        /**
         * Parsea el JSON contenido en el content data del request.
         *
         * @param[in] data   Datos binarios en formato JSON.
         * @param[in] dataLen   Cantidad de bytes que conforman los datos.
         *
         * @returns Un JSON con los datos conetnidos dentro del parametro 'data'.
         * */
        Json::Value parseContentData(const char* data, size_t dataLen) const;


        /**
         * Parsea el query string y lo transforma a JSON.
         *
         * @param[in] qStr   Datos en forma de query string.
         *
         * @returns Un JSON con los datos del query string.
         * */
        Json::Value parseQueryStringData(std::string qStr) const;


        /**
         * Utilidad que separa un par clave-valor mediante un signo '='.
         *
         * @param[in] keyVal    Contiene la clave y el valor separados por un '='.
         *
         * @returns Un objeto 'pair' con la clave y el valor en el primer y segundo lugar respectivamente.
         * */
        std::pair<std::string, std::string> toKeyValuePair(std::string keyVal) const;
};


#endif

