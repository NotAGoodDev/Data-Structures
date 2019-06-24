// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "bintree_eda.h"

template<typename T>
class bintree_ext : public bintree<T>
{
private:
	using Link = typename bintree<T>::Link;

	int nodos_rec(Link const& ptr)
	{
		if (ptr == nullptr)
			return 0;
		else
			return nodos_rec(ptr->left) + nodos_rec(ptr->right) + 1;
	}

	int hojas_rec(Link const& ptr)
	{
		if (ptr == nullptr)
			return 1;
		else
			if (ptr->left != nullptr
				&& ptr->right != nullptr)
				return hojas_rec(ptr->left) + hojas_rec(ptr->right);
			else if (ptr->left != nullptr)
				return hojas_rec(ptr->left);
			else
				return hojas_rec(ptr->right);
	}


	int altura_rec(Link const& ptr) const
	{
		if (ptr == nullptr)
			return 0;
		else
			return std::max(altura_rec(ptr->left), altura_rec(ptr->right)) + 1;
	}


public:
	bintree_ext() : bintree<T>(){};
	bintree_ext(bintree_ext<T> const& l, T const& e, bintree_ext<T> const& r) :bintree<T>(l, e, r){}

	int nodos()
	{
		if (this->raiz == nullptr)
			return 0;
		else
			return nodos_rec(this->raiz);
	}

	int hojas()
	{
		if (this->raiz == nullptr)
			return 0;
		else
			return hojas_rec(this->raiz);
	}

	int altura()
	{
		if (this->raiz == nullptr)
			return 0;
		else
			return altura_rec(this->raiz);
	}

	bintree_ext<T> leerArbol_ext(T vacio) {
		T raiz;
		std::cin >> raiz;
		if (raiz == vacio) { // es un árbol vacío
			return {};
		}
		else { // leer recursivamente los hijos
			auto iz = leerArbol_ext(vacio);
			auto dr = leerArbol_ext(vacio);
			return { iz, raiz, dr };
		}
	}

};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada

//	bintree<char> t = leerArbol('.');
//	std::cout << altura(t) << std::endl;

	bintree_ext<char> t;
	t = t.leerArbol_ext('.');

	// escribir sol
	std::cout << t.nodos() << " " << t.hojas() << " " << t.altura() << std::endl;
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