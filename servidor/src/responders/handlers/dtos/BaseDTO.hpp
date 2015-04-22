#ifndef BASE_DTO_H
#define BASE_DTO_H

#include "json/json.h"



/**
 * La clase base que define la interfaz de los DTOs.
 * */
class BaseDTO {
    public:
        
        /**
         * Almacena todos los datos del objeto dentro de un JSON.
         * */
        virtual Json::Value ToJSON() const = 0;

};


#endif

