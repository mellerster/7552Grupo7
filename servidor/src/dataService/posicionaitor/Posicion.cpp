#include "Posicion.hpp"

Posicion::Posicion(double latitud, double longitud, std::string texto)
{
	this->latitud = latitud;
	this->longitud = longitud;
	this->texto = texto;
}

Posicion::~Posicion(){
}

double Posicion::getLatitud()
{
	return this->latitud;
}

double Posicion::getLongitud()
{
	return this->longitud;
}

std::string Posicion::getTexto()
{
	return this->texto;
}

double Posicion::distancia(Posicion otraPosicion)
{
	// Distancia = raiz cuadrada de la suma del cuadrado de las diferencia de X e Y
	double dist = sqrt(pow((this->latitud - otraPosicion->latitud),2.0)+pow(this->longitud - otraPosicion->longitud,2.0));
}
