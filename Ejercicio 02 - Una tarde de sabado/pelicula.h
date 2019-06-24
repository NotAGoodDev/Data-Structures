#ifndef PELICULA_H
#define PELICULA_H

#include <string>
#include "horas.h"

class pelicula
{
public:

	horas iniPelicula, duracion, finPelicula;
	std::string nombre;

	pelicula(){}

	pelicula(horas ini, horas dur, std::string nom)
	{
		iniPelicula = ini;
		duracion = dur;
		nombre = nom;
		finPelicula = iniPelicula + duracion;
	}

	bool operator<(pelicula const& p)
	{
		return this->finPelicula < p.finPelicula ||
			(this->finPelicula == p.finPelicula
				&& this->nombre < p.nombre);
	}


private:

};


#endif // !PELICULA_H