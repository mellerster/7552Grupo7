#ifndef POSICION_H
#define POSICION_H
#include <string>
#include <cmath> 

class Posicion {
    public:
    	Posicion(double latitud, double longitud, std::string texto);
    	~Posicion();
    	double getLatitud();
    	double getLongitud();
    	std::string getTexto();
    	double distancia(Posicion otraPosicion);
    private:
    	double latitud;
    	double longitud;
    	std::string texto;
    	
};
#endif
