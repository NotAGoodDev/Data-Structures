// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

const int NAVEGABLE = 3;
const int NACE = 1;

struct tSol
{
	int caudal;
	int tramosNavegables;
	tSol() {}
	tSol(int c, int t) : caudal(c), tramosNavegables(t) {}
};

template<class T>
class bintree_ext : public bintree<T>
{
public:
	using Link = typename bintree<T>::Link;
	bintree_ext(){}
	bintree_ext(bintree_ext<T> const& l, T const& e, bintree_ext<T> const& r) : bintree<T>(l, e, r){}
	int aguaslimpias()
	{
		if (this->raiz == nullptr)
			return 0;

		tSol sol = aguaslimpias_rec(this->raiz);
		if (sol.caudal >= NAVEGABLE && sol.tramosNavegables > 0)
			sol.tramosNavegables--;
		return sol.tramosNavegables;
	}
	
private:
	//Si tiene der e izq -> embalse = 0
	//Si solo tiene 1 -> embalse > 0
	//Si no tiene ninguno -> nace

	tSol aguaslimpias_rec(Link const& l)
	{
		if(l->left == nullptr && l->right == nullptr)
			return tSol(NACE, 0);	//0 = tramos navegables
		else
		{
			tSol tramo;

			if (l->left != nullptr && l->right != nullptr)	//Tiene 2 hijos
			{
				tSol izq = aguaslimpias_rec(l->left);	//Llamada rec a la izq
				tSol der = aguaslimpias_rec(l->right);	//Llamada rec a la der
				tramo = tSol(izq.caudal + der.caudal - l->elem, izq.tramosNavegables + der.tramosNavegables);
			}
			else if (l->left != nullptr)	//Tiene hijo izquierdo
			{
				tramo = aguaslimpias_rec(l->left);	//Recorremos la rama izq
				tramo.caudal -= l->elem;
			}
			else if(l->right != nullptr)	//Tiene hijo derecho
			{
				tramo = aguaslimpias_rec(l->right);	//Recorremos la rama izq
				tramo.caudal -= l->elem;
			}

			if (tramo.caudal < 0)
				tramo.caudal = 0;

			if (tramo.caudal >= NAVEGABLE)	//Es navegable, aun quitandole caudal
				tramo = tSol(tramo.caudal, tramo.tramosNavegables + 1);

			return tramo;
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


// función que resuelve el problema
int resolver(bintree_ext<int> &arbol) {
	return arbol.aguaslimpias();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	bintree_ext<int> arbol = leerArbol_ext(-1);

	// escribir sol
	std::cout << resolver(arbol) << std::endl;
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