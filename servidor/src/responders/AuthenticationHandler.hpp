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
        AuthenticationHandler(IDataService &service);
        virtual ~AuthenticationHandler();


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

};


#endif

