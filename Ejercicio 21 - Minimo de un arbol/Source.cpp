// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "bintree_eda.h"

template<class T>
class bintree_ext : bintree<T>
{
private:
	using Link = typename bintree<T>::Link;

	T buscarMinimo_rec(Link const& n)
	{
		T izq, der;
			
		if (n->left != nullptr && n->right != nullptr)
		{
			izq = buscarMinimo_rec(n->left);
			der = buscarMinimo_rec(n->right);

			return std::min(n->elem, std::min(izq, der));
		}
		else if(n->left != nullptr)
			return izq = std::min(buscarMinimo_rec(n->left), n->elem);
		else if (n->right != nullptr)
			return der = std::min(buscarMinimo_rec(n->right), n->elem);
		else
			return n->elem;
	}

public:

	bintree_ext() : bintree<T>() {}
	bintree_ext(bintree_ext<T> const& l, T const& e, bintree_ext<T> const& r) : bintree<T>(l, e, r) {}
	// función que resuelve el problema
	T buscarMinimo()
	{
		return std::min(this->raiz->elem, buscarMinimo_rec(this->raiz));
	}

	bool esVacio()
	{
		return this->raiz == nullptr;
	}
};

template <typename T>
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

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	char n;
	std::cin >> n;
	if (!std::cin)
		return false;

	if (n == 'N')
	{
		bintree_ext<int> t = leerArbol_ext(-1);
		if (!t.esVacio())
			std::cout << t.buscarMinimo() << std::endl;
		else
			std::cout << -1 << std::endl;
	}
	else
	{
		bintree_ext<std::string> t = leerArbol_ext((std::string) "#");
		if(!t.esVacio())
			std::cout << t.buscarMinimo() << std::endl;
		else
			std::cout << "#" << std::endl;

	}

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