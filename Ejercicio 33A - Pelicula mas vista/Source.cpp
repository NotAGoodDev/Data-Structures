// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

#include <map>	//Para las fechas de la pelicula
#include <unordered_map>	//Servira para las veces que sale una pelicula
#include <set>	//No se puede unordered, porque tienen que salir en orden

using pelicula = std::string;
using fecha = std::string;
using veces = int;
using peliculaFecha= std::map<pelicula, fecha>;
using vFechas = std::vector<fecha>;	//Vector porque tienen que mostrarse en el orden de entrada, no ordenados

struct tSol
{
	veces v;
	vFechas fechas;
};

using peliculaDatos = std::unordered_map<pelicula, tSol>;
using conjuntoPeliculas = std::set<pelicula>;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int nDias;
	std::cin >> nDias;

	if (!std::cin)
		return false;

	peliculaDatos pd;

	for (int i = 0; i < nDias; i++)
	{
		fecha fAux;
		int nPeliculas;

		std::cin >> fAux;
		std::cin.ignore();
		std::cin >> nPeliculas;
		std::cin.ignore();
		for (int j = 0; j < nPeliculas; j++)
		{
			pelicula pAux;
			std::getline(std::cin, pAux);
			
			if (pd.count(pAux) > 0)	//Existe pelicula
			{
				pd[pAux].v++;
				if (pd[pAux].fechas.back() != fAux)	//No ha encontrado la fecha
					pd[pAux].fechas.push_back(fAux);
			}
			else
			{
				pd[pAux].v++;
				pd[pAux].fechas.push_back(fAux);
			}
		}
	}

	veces maxVeces = 0;
	conjuntoPeliculas cP;
	auto it = pd.begin();

	while (it != pd.end())
	{
		if (maxVeces < it->second.v)	//Hemos encontrado un maximo
		{
			cP.clear();
			cP.insert(it->first);
			maxVeces = it->second.v;
		}
		else if (maxVeces == it->second.v)	//Tenemos otro maximo
		{
			cP.insert(it->first);
		}

		it++;
	}

	// escribir sol
	std::cout << maxVeces << std::endl;
	for (auto it = cP.begin(); it != cP.end(); it++)
	{
		std::cout << it->data();
		
		for (int i = 0; i < pd[it->data()].fechas.size(); i++)
		{
			std::cout << " " << pd[it->data()].fechas[i];
		}
		std::cout << std::endl;
	}

	std::cout << "---" << std::endl;

	return true;

}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	while (resuelveCaso())
		;


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}