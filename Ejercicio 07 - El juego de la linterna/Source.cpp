// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
#include <vector>

using vector = std::vector<int>;
using stack = std::stack<int>;
bool resolverAlto(std::stack<int> s, int medio)
{
	s.pop();
	while(s.top() != NULL)
	{
		if (s.top() < medio)
			return true;

		s.pop();
	}

	return false;
}

// función que resuelve el problema
bool resolver(vector const& v) {
	stack s;
	
	int i = v.size() - 1, mediano = -1;
	s.push(v[i]);

	i--;
	while (i >= 0)
	{
		while (!s.empty() && v[i] > s.top())
		{
			mediano = s.top();
			s.pop();
		}

		if (v[i] < mediano)
			return false;
		else
			s.push(v[i]);

		i--;
	}

	return true;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int n;
	std::cin >> n;
	if (!std::cin)
		return false;

	vector v(n);
	for (int i = 0; i < n; i++)
		std::cin >> v[i];
		

	// escribir sol
	if (resolver(v))
		std::cout << "SIEMPRE PREMIO" << std::endl;
	else
		std::cout << "ELEGIR OTRA" << std::endl;	//No se ha encontrado una combinacion

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