#include "Posicionador.hpp"

Posicionador::Posicionador()
{
	this->LoadUbicaciones();
}


Posicionador::~Posicionador(){
	for (std::list<Posicion>::iterator it = ubicaciones.begin(); it != ubicaciones.end(); it++)
	{
		delete *it;
	}
}

Posicionador::LoadLocaciones(){
	ifstream locaciones ("locaciones");
	std::string line;
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			double latitud;
			double longitud;
			std::string texto;
			size_t posPipeLat = s.find("|");
			latitud = std::stod (s.substr(0, posPipeLat));
			size_t posPipeLong = s.find("|",posPipeLat+1);
			longitud = std::stod (s.substr(posPileLat+1, posPileLong));
			texto = s.substr(posPileLong+1);
			ubicaciones.add(new Posicion(latitud,longitud,texto));
		}
		locaciones.close();
	}
}

std::string Posicionador::getLugarMasCercano(double latitud, double longitud)
{
	double minDistancia = 10000;
	std::string texto = "";
	Posicion posicion(latitud, longitud, "");
	for (std::list<Posicion>::iterator it = ubicaciones.begin(); it != ubicaciones.end(); it++)
	{
		double distancia = it->distancia(posicion);
		if(distancia < minDistancia)
		{
			minDistancia = distancia;
			texto = it->getTexto();
		}
	}
	return texto;
}
