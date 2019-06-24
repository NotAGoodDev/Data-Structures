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
	void invertirLista()
	{
		Nodo * pAuxAnt = nullptr;
		Nodo * pAuxAct = this->prim;
		Nodo * pAuxSig = this->prim->sig;

		while (pAuxAct != nullptr)
		{
			pAuxSig = pAuxAct->sig;  
			pAuxAct->sig = pAuxAnt;
			pAuxAnt = pAuxAct;
			pAuxAct = pAuxSig;
		}

		this->prim = pAuxAnt;
		this->ult = nullptr;
		
	}

	void mostrarLista()
	{
		Nodo * pAux = this->prim;

		while (pAux != nullptr)
		{
			std::cout << pAux->elem << " ";
			pAux = pAux->sig;
		}
		std::cout << std::endl;
	}
};

void resolver(cola<int> & q) {
	q.invertirLista();
	q.mostrarLista();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int n;
	std::cin >> n;

	if (!std::cin)
		return false;

	cola<int> q;

	while (n != 0)
	{
		q.push(n);
		std::cin >> n;
	}

	if (q.size() == 0)
		std::cout << std::endl;
	else
		resolver(q);

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