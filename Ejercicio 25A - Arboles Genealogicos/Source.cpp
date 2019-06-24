// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

struct tSol
{
	bool esAG;
	int nGeneraciones;
	
	tSol(){}
	tSol(bool e, int n) : esAG(e), nGeneraciones(n){}
};

template <class T>
class bintree_ext : public bintree<T>
{
private:
	using Link = typename bintree<T>::Link;
	tSol esArbolGeneracional_rec(Link const& l)
	{
		if (l->left != nullptr && l->right != nullptr)	//Existen los dos hijos
		{
			if (l->elem - 18 >= l->left->elem
				&& l->elem - 18 >= l->right->elem)	//Cumplen con la primera condicion
				if (l->left->elem >= l->right->elem + 2)	//Cumplen la segunda condicion
				{
					tSol izq = esArbolGeneracional_rec(l->left);
					tSol der = esArbolGeneracional_rec(l->right);

					if (izq.esAG && der.esAG)
						return { true, std::max(der.nGeneraciones, izq.nGeneraciones) + 1 };

				}
		}
		else if (l->left != nullptr)	//Solo tiene un hijo
			if (l->elem - 18 >= l->left->elem)
			{
				tSol sol = esArbolGeneracional_rec(l->left);
				return { sol.esAG, sol.nGeneraciones + 1 };
			}
		else if (l->right != nullptr)	//No es arbol generacional, ya que de existir, estaria a la izquierda
			return { false, 0 };
		else	//No tiene hojas, es hijo, por lo tanto, arbol generacional de 1 hijo
			return { true, 1 };

		return { false, 0 };
	}

public:
	bintree_ext(){}
	bintree_ext(bintree_ext const& l, T const& e, bintree_ext const& r) : bintree<T>(l, e, r){}

	tSol esArbolGeneracional() {
		if (this->raiz != nullptr)
			return esArbolGeneracional_rec(this->raiz);
		else
			return { true, 0 };
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
void resuelveCaso() {
	// leer los datos de la entrada

	bintree_ext<int> t = leerArbol_ext(-1);
	tSol sol = t.esArbolGeneracional();

	// escribir sol
	if (sol.esAG)
		std::cout << "SI " << sol.nGeneraciones << std::endl;
	else
		std::cout << "NO" << std::endl;


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