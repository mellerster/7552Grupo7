#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <string>
#include <vector>


/**
 * Clase base de todos los objetos capaces de manejar pedidos.
 * */
class RequestHandler {
    public:
        RequestHandler();
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
};


#endif

