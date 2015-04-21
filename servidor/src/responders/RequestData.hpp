#ifndef REQUEST_DATA_H
#define REQUEST_DATA_H

#include <string>

#include "json/json.h"



/**
 * Contiene los datos que vienen desde el cliente junto con el pedido.
 * */
class RequestData {
    public:
        /**
         * Extrae los datos necesarios del JSON.
         *
         * @param[in] jsonData  De donde extrae sus datos.
         * */
        RequestData(Json::Value jsonData);
        virtual ~RequestData();


        /**
         * El token que define la conexion entre el servidor y un cliente activo.
         * */
        std::string GetToken() const;
};

#endif

