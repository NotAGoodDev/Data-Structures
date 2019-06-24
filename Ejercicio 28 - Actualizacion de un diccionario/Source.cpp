// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
//Para este ejercicio utilizo los diccionarios para ordenar los alumnos
// alfabeticamente y ver si tiene un balance positivo o negativo
// si es negativo, decremento el valor, si es positivo, incremento
// función que resuelve el problema
using alumno = std::string;
using balance = int;
using map = std::map<alumno, balance>;
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int n;
	std::cin >> n;

	if (n == 0)
		return false;

	map tabla;
	std::string basura;
	std::getline(std::cin, basura);	//Como hemos usado un cin, el salto de linea

	for (int i = 0; i < n; i++)
	{
		std::string nombre, resultado;
		std::getline(std::cin, nombre);
		std::getline(std::cin, resultado);

		if (resultado == "CORRECTO")
			tabla[nombre]++;	//Sumamos 1 al resultado de la entrada del diccionario
		else if (resultado == "INCORRECTO")
			tabla[nombre]--;	//Restamos 1 """""
	}

	// escribir sol
	for(auto c : tabla)
		if (c.second != 0)
			std::cout << c.first << ", " << c.second << std::endl;
	
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