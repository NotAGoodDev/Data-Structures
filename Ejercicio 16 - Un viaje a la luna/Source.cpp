// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "persona.h"
#include "list_eda.h"

class Predicate
{
public:
	Predicate() {}
	Predicate(int n, int x) : min(n), max(x) {}

	bool operator()(persona & p)
	{
		int edad = p.getEdad();
		return min <= edad && max >= edad;
	}

private:
	int min, max;

};

template <class T>
class lista : public list<persona>
{
public:
	void remove_if(Predicate pred)
	{
		for (int i = 0; i < this->nelems; i++)
		{
			auto it = this->begin();
			while (it != this->end())
			{
				if (!pred(*it))
				{
					auto aux = it;
					it++;
					this->erase(aux);
				}
				else
					it++;
			}
		}
	}


private:

};


// función que resuelve el problema
template <class T>
void resolver(lista<T> & l, int const& NUM, int const& MIN, int const& MAX) {

	l.remove_if(Predicate(MIN, MAX));

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int n, min, max;
	std::cin >> n >> min >> max;
	if (n == 0 && min == 0 && max == 0)
		return false;

	lista<persona> l;
	for (int i = 0; i < n; i++)
	{
		int edad;
		std::string nombre;
		std::cin >> edad;
		std::cin.ignore();
		std::getline(std::cin, nombre);

		l.insert(l.end(), persona(edad, nombre));
	}

	resolver(l, n, min, max);
	auto it = l.begin();
	while (it != l.end())
	{
		std::cout << it->getNombre() << std::endl;
		it++;
	}
	
	std::cout << "---" << std::endl;

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