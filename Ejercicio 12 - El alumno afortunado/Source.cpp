// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>

using queue = std::queue<int>;
// función que resuelve el problema
int resolver(queue &q, int const& SALTO) {
	int i = 0;
	while (q.size() > 1)
	{
		int temp;
		if (i == SALTO)
		{
			q.pop();
			i = 0;
		}
		temp = q.front();
		q.pop();
		q.push(temp);
		i++;
	}

	return q.front();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int n, salto;
	std::cin >> n >> salto;
	if (n == 0 && salto == 0)
		return false;

	queue q;

	for (int i = 0; i < n; i++)
		q.push(i + 1);

	std::cout << resolver(q, salto) << std::endl;

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