#include "Posicionador.hpp"

Posicionador::Posicionador()
{
	this->LoadLocaciones();
}


Posicionador::~Posicionador(){ }


void Posicionador::LoadLocaciones(){
    std::ifstream locaciones ("locaciones");
	std::string line;
	if (locaciones.is_open())
	{
		while ( getline (locaciones,line) )
		{
			size_t posPipeLat = line.find("|");
			size_t posPipeLong = line.find("|",posPipeLat+1);

			double latitud = std::stod (line.substr(0, posPipeLat));
			double longitud = std::stod (line.substr(posPipeLat+1, posPipeLong));
			std::string texto = line.substr(posPipeLong+1);

            Posicion p(latitud,longitud,texto);
			ubicaciones.push_back(p);
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
