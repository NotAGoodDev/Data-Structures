// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stack>
#include <queue>

// función que resuelve el problema
bool esVocal(char const& c)
{
	return c == 'a' || c == 'A'
		|| c == 'e' || c == 'E'
		|| c == 'i' || c == 'I'
		|| c == 'o' || c == 'O'
		|| c == 'u' || c == 'U';
}

std::string cifrado2(std::string const& s) {
	std::string aux;
	std::stack<char> pila;
	size_t i = 0;

	while (i < s.size())
	{
		if (esVocal(s[i]))
		{
			while (pila.size() > 0)
			{
				char c = pila.top();
				pila.pop();
				aux.push_back(c);
			}

			aux.push_back(s[i]);
		}
		else
			pila.push(s[i]);

		i++;
	}

	while (pila.size() > 0)
	{
		char c = pila.top();
		pila.pop();
		aux.push_back(c);
	}


	return aux;
}

std::string cifrado1(std::string const& s) {
	std::string aux;
	std::stack<char> pila;
	std::queue<char> cola;

	for (size_t i = 0; i < s.size(); i++)
		if (i % 2 == 0)
			cola.push(s[i]);
		else
			pila.push(s[i]);

	while (cola.size() > 0)
	{
		aux.push_back(cola.front());
		cola.pop();
	}

	while (pila.size() > 0)
	{
		aux.push_back(pila.top());
		pila.pop();
	}

	return aux;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada

	if (!std::cin)
		return false;
	std::string s;

	std::getline(std::cin, s);

	s = cifrado1(s);
	s = cifrado2(s);

	std::cout << s << std::endl;

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