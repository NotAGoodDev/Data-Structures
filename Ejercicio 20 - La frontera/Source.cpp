// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "bintree_eda.h"

using vector = std::vector<int>;

template <class T>
class bintree_ext : public bintree<T> {

	using Link = typename bintree<T>::Link;

public:

	bintree_ext() : bintree<T>() {}

	bintree_ext(bintree_ext<T> const& l, T const& e, bintree_ext<T> const& r) : bintree<T>(l, e, r) {}

	bintree_ext<T> leerArbol(int vacio) {
		T raiz;
		std::cin >> raiz;
		if (raiz == vacio) { // es un árbol vacío
			return {};
		}
		else { // leer recursivamente los hijos
			auto iz = leerArbol(vacio);
			auto dr = leerArbol(vacio);
			return { iz, raiz, dr };
		}
	}

	void frontera(vector &v)
	{
		if (this->raiz != nullptr)
			frontera_rec(this->raiz, v);
	}


	void frontera_rec(Link const& l,  vector &v)
	{
		if (l->left == nullptr
			&& l->right == nullptr)
			v.push_back(l->elem);
		else if (l->left != nullptr
			&& l->right != nullptr)
		{
			frontera_rec(l->left, v);
			frontera_rec(l->right, v);
		}
		else if (l->left != nullptr)
			frontera_rec(l->left, v);
		else
			frontera_rec(l->right, v);
	}
};

// función que resuelve el problema
vector resolver() {
	vector v;
	bintree_ext<int> bt;
	bt = bt.leerArbol(-1);
	bt.frontera(v);
	return v;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	vector sol;
	sol = resolver();

	// escribir sol
	for (int i = 0; i < sol.size(); i++)
		std::cout << sol[i] << " ";

	std::cout << std::endl;
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