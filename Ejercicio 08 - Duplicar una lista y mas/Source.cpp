// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include "queue_eda.h"

template<class T>
class lista : public queue<T>
{
public:
	using Nodo = typename queue<T>::Nodo;

	void duplicar()
	{
		Nodo * a = nullptr;
		Nodo * b = this->prim;

		while (b != nullptr)
		{
			a = new Nodo(b->elem, b->sig);
			b->sig = a;
			b = b->sig->sig;
		}

		this->ult = a;
		this->nelems *= 2;

	}

	void mostrar()
	{
		Nodo * a = this->prim;
		std::cout << this->nelems << std::endl;

		while (a != nullptr && a->elem != 0)
		{
			std::cout << a->elem << " ";
			a = a->sig;
		}

		std::cout << std::endl;
	}
};

void resolver(lista<int> & q) {
	q.duplicar();
	q.mostrar();
}


void resolver2(lista<int> &q)
{
	int i;
	std::cin >> i;

	while (i != 0) {
		q.push(i);
		std::cin >> i;
	}

	int n;
	std::cin >> n;
	for (int i = 0; i < n; i++)
		q.pop();

	q.mostrar();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	
	int i;
	std::cin >> i;

	if (!std::cin)
		return false;
	
	lista<int> q;

	while (i != 0) {
		q.push(i);
		std::cin >> i;
	}

	resolver(q);
	resolver2(q);
	
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