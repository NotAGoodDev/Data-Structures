// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "bintree_eda.h"

struct tSol
{
	std::string nombre;
	int contador;

	tSol(){}
	tSol(std::string n, int c) : nombre(n), contador(c) {}
};

template <class T>
class bintree_ext : public bintree<T>
{
public:
	using Link = typename bintree<T>::Link;

	bintree_ext() {}
	bintree_ext(bintree_ext<T> const& l, T const& e, bintree_ext<T> const& r) : bintree<T>(l, e, r) {}

	tSol resolver()
	{
		if (this->raiz == nullptr)
			return tSol();

		return resolver_rec(this->raiz);
	}

private:
	const std::string DRAGON = "Dragon";

	tSol resolver_rec(Link const& l)
	{
		if (l->left != nullptr && l->right != nullptr)
		{
			tSol izq = resolver_rec(l->left);
			tSol der = resolver_rec(l->right);
			tSol sol;

			if (der.contador < izq.contador)
				sol = der;
			else
				sol = izq;

			if (l->elem == DRAGON)
				return tSol(sol.nombre, sol.contador + 1);

			return sol;
		}
		else if (l->left == nullptr && l->right == nullptr)	//Es hoja
		{
			return tSol(l->elem, 0);
		}
		else if (l->left != nullptr)	//Hay mas valores a la izquierda
		{
			if (l->elem == DRAGON)
			{
				tSol aux = resolver_rec(l->left);
				return tSol(aux.nombre, aux.contador + 1);
			}
			else
			{
				return resolver_rec(l->left);
			}
		}
		else if (l->right != nullptr)
		{
			if (l->elem == DRAGON)
			{
				tSol aux = resolver_rec(l->right);
				return tSol(aux.nombre, aux.contador + 1);
			}
			else
			{
				return resolver_rec(l->right);
			}
		}
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
	std::string tipo = "...";
	bintree_ext<std::string> arbol = leerArbol_ext(tipo);
	tSol sol = arbol.resolver();

	// escribir sol
	std::cout << sol.nombre << " " << sol.contador << std::endl;

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