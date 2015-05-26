#ifndef POSICIONADOR_H
#define POSICIONADOR_H
#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "IPosicionador.hpp"
#include "Posicion.hpp"



class Posicionador : public IPosicionador {
    public:

        /** Constructor base del Posicionador
         *
         * */
        Posicionador();

        virtual ~Posicionador();

        /**
         * Obtiene el lugar mas cercano a una latitud y longitud.
         *
         * @return  String con el texto del lugar mas cercano.
         * */
        std::string getLugarMasCercano(double latitud, double longitud);

    private:
    	/**
    	 * Lista con los lugares
    	*/
    	std::list<Posicion> ubicaciones;
        
        /**
         * Carga los lugares desde el archivo.
         *
         * */
        void LoadLocaciones();
};
#endif
