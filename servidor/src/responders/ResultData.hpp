#ifndef RESULT_DATA_H
#define RESULT_DATA_H

#include "json/json.h"



/**
 * Base de todos los objetos que serán transformados en JSON.
 * */
class ResultData {
    public:
        ResultData();
        virtual ~ResultData();


        /**
         * Alamcena todos los datos contenidos en esta clase en un JSON.
         *
         * @returns     Un JSON con todos los datos del objeto.
         * */
        virtual Json::Value ToJson() const;

};


#endif

