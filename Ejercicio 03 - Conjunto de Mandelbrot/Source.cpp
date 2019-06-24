// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "complejo.h"

using vector = std::vector<float>;
// función que resuelve el problema
bool resolver(complejo z, complejo const& c, int n) {	//zn, c, n
	if (n == 0)
		return true;
	else
		if (z.calculaModulo() <= (float) 2.0)
			resolver(z * z + c, c, n - 1);
		else
			throw std::invalid_argument("NO");

	return false;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	float real, imaginario;
	int n;
	std::cin >> real >> imaginario >> n;
	complejo c(real, imaginario);


	// escribir sol
	try {
		resolver(complejo(0, 0), c, n);		// z0, c, n
		std::cout << "SI" << std::endl;
	}
	catch(std::invalid_argument &ia){
		std::cout << ia.what() << std::endl;
	}

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
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}