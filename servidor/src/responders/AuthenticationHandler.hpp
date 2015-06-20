#ifndef AUTHENTICATION_HANDLER_H
#define AUTHENTICATION_HANDLER_H

#include <string>

#include "json/json.h"
#include "IDataService.hpp"



/**
 * Valida que el cliente tenge los permisos necesarios para acceder al recurso solicitado.
 * */
class AuthenticationHandler {
    public:
        AuthenticationHandler(IDataService &service) : m_dataService(service) { }
        virtual ~AuthenticationHandler() { }


        /** Carga los parametros del pedido.
         *
         * @param[in] queryString   El query string del request sin el "?" del inicio.
         * @param[in] data  Los datos binarios del pedido, suelen ser POST.
         * @param[in] data_len  La cantidad de bytes de datos binarios.
         * */
        void LoadParameters(const char* queryString, const char* data, size_t data_len);


        /** Indica si el cliente tiene los permisos necesarios para acceder al recurso pedido.
         *
         * @param[in] httpVerb  Indica el tipo de pedido realizado.
         * @param[in] httpURI   Indica el recurso al que se quiere acceder.
         *
         * @returns true si el cliente esta autorizado, false si no.
         * */
        bool IsResourceAccesible(std::string httpVerb, std::string httpURI);


    protected:
        IDataService &m_dataService;


        /** El JSON correspondiente al 'Content data'.
         * */
        Json::Value m_parsedParameters_ContentData;


        /** El JSON correspondiente al 'query string'.
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

