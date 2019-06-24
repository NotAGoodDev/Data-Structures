// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include <map> 
#include <vector>
#include <sstream>
#include <string>

// función que resuelve el problema

using palabra = std::string;
using linea = int;
using lineas = std::vector<linea>;
using diccionario = std::map<palabra, lineas>;

void leerLinea(diccionario &d, std::string const& lineaLeida, linea const& nLinea) {
	std::stringstream ss(lineaLeida);
	palabra p;

	while (ss)
	{
		ss >> p;
		if (p.size() > 2)
		{
			for (int i = 0; i < p.size(); i++)	//A minusculas
				p[i] = tolower(p[i]);

			if (d[p].size() == 0 || d[p].back() != nLinea)	//Para que no de nullpointer, y buscamos el ultimo valor
				d[p].push_back(nLinea);	//Aniadimos la linea
		}
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int n;
	std::cin >> n;
	if (n == 0)
		return false;

	std::cin.ignore();	//Primer caracter

	diccionario d;
	for (size_t i = 1; i <= n; i++)
	{
		std::string linea;
		std::getline(std::cin, linea);

		leerLinea(d, linea, i);
	}

	// escribir sol
	auto it = d.begin();	//Para recorrer el diccionario
	while (it != d.end())	//Mientras no sea el final
	{
		std::cout << it->first << " ";	//Mostramos la palabra

		for (int i = 0; i < it->second.size(); i++)	//Mostramos las lineas de la palabra (vector)
			std::cout << it->second[i] << " ";

		it++;
		std::cout << std::endl;
	}

	std::cout << "----" << std::endl;

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