// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <string>
#include <algorithm>
#include "pelicula.h"

using vector = std::vector<horas>;
using vectorPeliculas = std::vector<pelicula>;

//Mostrar horas
std::ostream& operator<<(std::ostream& out, horas h)
{

	out << std::setfill('0') << std::setw(2) << h.hora << ":"
		<< std::setfill('0') << std::setw(2) << h.minuto << ":"
		<< std::setfill('0') << std::setw(2) << h.segundo;

	return out;
}

//Mostrar peliculas
std::ostream& operator<<(std::ostream& out, pelicula p)
{
	out << p.finPelicula << " " << p.nombre << std::endl;
	return out;
}

//Entrada de horas
std::istream& operator>> (std::istream &in, horas &h)
{

	char basura;	//Para leer los ':' 
	in >> h.hora >> basura >> h.minuto >> basura >> h.segundo;

	return in;
}

// función que resuelve el problema
void resolver(vectorPeliculas & vP)
{
	std::sort(vP.begin(), vP.end());	//Ordena el vector con la sobrecarga del operador <
	for (int i = 0; i < vP.size(); i++)
		std::cout << vP[i];	//Mostrar peliculas con sobrecarga
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int n;
	std::cin >> n;
	if (n == 0)
		return false;
	
	vectorPeliculas vP(n);

	for (int i = 0; i < n; i++)
	{
		horas ini, dur;
		std::string nombre;
		std::cin >> ini >> dur;	//Guardamos el inicio y la duracion
		std::getline(std::cin, nombre);	//Guardamos el nombre de la pelicula en el vector de Peliculas


			pelicula p(ini, dur, nombre);	//Constructor pelicula (Calcula el final automaticamente)
			vP[i] = p;


	}

	// escribir sol
	resolver(vP);
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