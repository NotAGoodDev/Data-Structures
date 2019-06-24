// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include "queue_eda.h"



// función que resuelve el problema
template <class T>
class cola : public queue<T>
{
private:
	using Nodo = typename queue<T>::Nodo;

public:
	void aniadirLista(cola<int> &q, int const& POS)
	{
		
		Nodo * pSig = nullptr;
		Nodo * act = this->prim;

		for (int i = 0; i < POS - 1; i++)	//Para colocar el puntero
			act = act->sig;

		if (POS > 0)
		{
			pSig = act->sig;
			act->sig = q.prim;
			q.ult->sig = pSig;
		}
		else
		{
			q.ult->sig = act;
			this->prim = q.prim;
		}

		this->nelems += q.nelems;
		q.prim = nullptr;
	}

	void mostrar() const
	{
		Nodo * act = this->prim;
		for (int i = 0; i < this->nelems; i++)
		{
			std::cout << act->elem << " ";
			act = act->sig;
		}

		std::cout << std::endl;
	}
};

void resolver(cola<int> &q1, cola<int> &q2, int const& POS) {
	q1.aniadirLista(q2, POS);
	q1.mostrar();
}

void leerElementos(cola <int> & q, int const& N)
{
	for (int i = 0; i < N; i++)
	{
		int j;
		std::cin >> j;
		q.push(j);
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int n, pos;
	std::cin >> n;

	if (!std::cin)
		return false;

	cola<int> q1;
	leerElementos(q1, n);

	cola<int> q2;
	std::cin >> n >> pos;
	leerElementos(q2, n);

	resolver(q1, q2, pos);

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