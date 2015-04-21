#ifndef RESPONSE_H
#define RESPONSE_H

#include <vector>



/**
 * Objecto que contiene los datos de las respuestas de los request handler.
 * */
class Response {
    public:
        Response(int statusCode);
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
        std::vector<char> m_dataContainer;  // TODO: Evaluar un stringstream

};


#endif

