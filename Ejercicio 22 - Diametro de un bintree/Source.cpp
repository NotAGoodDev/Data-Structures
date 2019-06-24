// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

template <class T>
class bintree_ext : public bintree<T>
{
private:
	using Link = typename bintree<T>::Link;

	int diametro_rec(Link const& l, int &max)
	{
		if (l->left == nullptr
			&& l->right == nullptr)
			return 1;
		else if (l->left != nullptr
			&& l->right != nullptr)
		{
			int der = diametro_rec(l->right, max);
			int izq = diametro_rec(l->left, max);
			int ramaHorizontal = izq + der + 1;
			int ladoMaximo = std::max(izq, der) + 1;

			if (max < ramaHorizontal)
				max = ramaHorizontal;
			return ladoMaximo;

		}
		else if (l->left != nullptr)
			return diametro_rec(l->left, max) + 1;
		else
			return diametro_rec(l->right, max) + 1;
	}

public:
	bintree_ext(){}
	bintree_ext(bintree_ext<T> const& l, T const& e, bintree_ext<T> const& r) : bintree<T>(l, e, r) {}

	int diametro()
	{
		if (this->raiz != nullptr)
		{
			int max = 1;
			int resultadoTotal = diametro_rec(this->raiz, max);

			if (resultadoTotal > max)
				return resultadoTotal;
			else
				return max;
		}
		else
			return 0;
	}
};

template<typename T>
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

// función que resuelve el problema

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	bintree_ext<char> t = leerArbol_ext('.');

	std::cout << t.diametro() << std::endl;
	// escribir sol


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