// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

using clave = std::string;
using valor = int;
using diccionario = std::map<clave, valor>;

void leerDiccionario(diccionario & d)
{
	std::string linea;
	std::getline(std::cin, linea);
	std::stringstream ss(linea);	//Libreria sstream

	while (ss)
	{
		clave auxClave;
		valor auxValor;
		ss >> auxClave;
		ss >> auxValor;

		if(auxClave != "")
			d.insert({auxClave, auxValor});
	}
}

void escribir(char const& c, std::vector<clave> const& v)
{
	if (v.size() > 0)
	{
		std::cout << c << " ";

		for (size_t i = 0; i < v.size(); i++)
			std::cout << v[i] << " ";

		std::cout << std::endl;
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	diccionario antiguo, nuevo;
	leerDiccionario(antiguo);	//Evitamos codigo repetido
	leerDiccionario(nuevo);

	std::vector<clave> aniadidos;	//Llevaremos las claves aniadidas
	std::vector<clave> borrados;	
	std::vector<clave> modificados;

	auto itAntiguo = antiguo.begin();
	auto itNuevo = nuevo.begin();

	while (itAntiguo != antiguo.end()	//Recorremos los diccionarios hasta que uno
		&& itNuevo != nuevo.end())			//finaliza
	{
		if (itAntiguo->first > itNuevo->first)	//Si por ejemplo, a > b, entonces, ponemos el nuevo en aniadidos
		{
			aniadidos.push_back(itNuevo->first);
			itNuevo++;
		}
		else if (itAntiguo->first < itNuevo->first)
		{
			borrados.push_back(itAntiguo->first);
			itAntiguo++;
		}
		else	//Si son iguales, pueden pasar dos cosas
		{
			if (itAntiguo->second != itNuevo->second)	//Que tengan distintos numeros, y se aniaden a modificados
				modificados.push_back(itAntiguo->first);
			itAntiguo++;	//O no se hace nada, y se pasa a la siguiente clave
			itNuevo++;
		}
	}

	while (itAntiguo != antiguo.end())	//Por si no ha llegado al final en una de las dos iteraciones
	{
		borrados.push_back(itAntiguo->first);
		itAntiguo++;
	}

	while (itNuevo != nuevo.end())	// "
	{
		aniadidos.push_back(itNuevo->first);
		itNuevo++;
	}

	// escribir sol
	if (aniadidos.size() == 0
		&& borrados.size() == 0
		&& modificados.size() == 0)
		std::cout << "Sin cambios" << std::endl;
	else
	{
		escribir('+', aniadidos);	//Escribe en pantalla, si es vacio, no hace nada
		escribir('-', borrados);
		escribir('*', modificados);
	}

	std::cout << "----" << std::endl;
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	int numCasos;
	std::cin >> numCasos;
	std::cin.ignore();
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}