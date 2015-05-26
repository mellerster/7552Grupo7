#ifndef IPOSICIONADOR_H
#define IPOSICIONADOR_H

#include <string>



/** La interfaz del sistema de triangulación de coordenadas.
 * */
class IPosicionador {
    public:

        /** Obtiene el lugar mas cercano a una latitud y longitud.
         *
         * @return  String con el texto del lugar mas cercano.
         * */
        virtual std::string getLugarMasCercano(double latitud, double longitud) = 0;


        virtual ~IPosicionador() { } 
};


#endif

