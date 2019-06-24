// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>


// función que resuelve el problema
void resolver(int tam, int &becarios, int const& K)
{
	int hijo;
	std::cin >> hijo;

	if (hijo != 0)
		for (int i = 0; i < hijo; i++)
			resolver(tam + 1, becarios, K);
	else if (tam > K)
			becarios++;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int k;
	std::cin >> k;

	if (!std::cin)
		return false;	

	int tam = 1, becarios = 0;
	resolver(tam, becarios, k);

	std::cout << becarios << std::endl;

	// escribir sol

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