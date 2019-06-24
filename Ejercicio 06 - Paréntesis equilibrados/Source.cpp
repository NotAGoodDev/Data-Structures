// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stack>


// función que resuelve el problema

bool esAbierto(char const& c)
{
	return c == '('
		|| c == '{'
		|| c == '[';
}

bool esCerrado(char const& c)
{
	return c == ')'
		|| c == '}'
		|| c == ']';
}

bool coincidenAperturas(char const& c1, char const& c2)
{
	return (c1 == '(' && c2 == ')')
		|| (c1 == '{' && c2 == '}')
		|| (c1 == '[' && c2 == ']');
}

bool resolver(std::string const& s) {
	std::stack<char> pila;
	for (int i = 0; i < s.size(); i++)
	{
		if (esAbierto(s[i])
			|| (esCerrado(s[i]) && pila.size() == 0))
			pila.push(s[i]);	//Se mete a la pila
		else if (pila.size() > 0)
		{
			//char elementoCerrado = ((int)pila.top()) + 1;			Era buena idea, pero no funciona
		
			if (coincidenAperturas(pila.top(), s[i]))	//Es cerrado y concuerda
				pila.pop();	//Es cerrado, se saca de la pila
			else if (esCerrado(s[i]))	//Si es cerrado, pero no es el suyo propio
				return false;
		}
	}

	return pila.size() == 0;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	std::string s;
	std::getline(std::cin, s);
	if (!std::cin)
		return false;

	if (resolver(s))
		std::cout << "SI" << std::endl;
	else
		std::cout << "NO" << std::endl;

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