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
	struct cotas
	{
		int min;
		int max;

		cotas(){}
		cotas(int n, int x) : min(n), max(x) {}
	};

	bool esSBT_rec(Link const& l, cotas const c)
	{
		if (l->left != nullptr
			&& l->right != nullptr)
		{
			if (l->left->elem < l->elem
				&& l->right->elem > l->elem)
				if (c.min == -1		//No estan inicializadas las cotas
					&& c.max == -1)
				{
					return esSBT_rec(l->left, {-1, l->elem}) && esSBT_rec(l->right, {l->elem, -1});	//Izq no tiene cota inf, Der no tiene cota sup
				}
				else if (c.min == -1 && c.max != -1)	//No tiene cota inferior
				{
					if(l->elem < c.max)
						return esSBT_rec(l->left, { -1, l->elem }) && esSBT_rec(l->right, { l->elem, c.max });	//Izq no tiene cota inf, Der no tiene cota sup
				}
				else if (c.min != -1 && c.max == -1)	//No tiene cota superior
				{
					if (l->elem > c.min)
						return esSBT_rec(l->left, { c.min, l->elem }) && esSBT_rec(l->right, { l->elem, -1 });	//Der no tiene cota sup
				}
				else
					if (l->elem > c.min && l->elem < c.max)
						return esSBT_rec(l->left, { c.min , l->elem }) && esSBT_rec(l->right, { l->elem, c.max });	//Izq tiene cota inf, Der tiene cota sup
		}
		else if (l->left != nullptr)
		{
			if (l->left->elem < l->elem)
				if (c.min == -1		//No estan inicializadas las cotas
					&& c.max == -1)
				{
					return esSBT_rec(l->left, { -1, l->elem });
				}
				else if (c.min == -1 && c.max != -1)	//No tiene cota inferior
				{
					if (l->elem < c.max)
						return esSBT_rec(l->left, { -1, l->elem });	//No tiene cota inf
				}
				else if (c.min != -1 && c.max == -1)	//No tiene cota superior
				{
					if (l->elem > c.min)
						return esSBT_rec(l->left, { c.min, l->elem });
				}
				else
					if(l->elem > c.min && l->elem < c.max)
						return esSBT_rec(l->left, { c.min , l->elem });
		}
		else if (l->right != nullptr)
		{
			if (l->right->elem > l->elem)
				if (c.min == -1		//No estan inicializadas las cotas
					&& c.max == -1)
				{
					return esSBT_rec(l->right, { l->elem, -1 });
				}
				else if (c.min == -1 && c.max != -1)
				{
					if (l->elem < c.max)
						return esSBT_rec(l->right, { l->elem, c.max });
				}
				else if (c.min != -1 && c.max == -1)
				{
					if(l->elem > c.min)
						return esSBT_rec(l->right, { l->elem, -1 });
				}
				else
					if (l->elem > c.min && l->elem < c.max)
						return esSBT_rec(l->right, { l->elem, c.max });
		}
		else
			if (c.min == -1		//No estan inicializadas las cotas
				&& c.max == -1)
			{
				return true;
			}
			else if (c.min == -1 && c.max != -1)
			{
				if (l->elem < c.max)
					return true;
			}
			else if (c.min != -1 && c.max == -1)
			{
				if (l->elem > c.min)
					return true;
			}
			else
				if (l->elem > c.min && l->elem < c.max)
					return true;

		return false;
	}

public:
	bintree_ext(){}
	bintree_ext(bintree_ext const& l, T const& e, bintree_ext const& r) : bintree<T>(l, e, r){}

	bool esSBT()
	{
		if (this->raiz != nullptr) 
		{
			cotas c(-1, -1);
			return esSBT_rec(this->raiz, c);
		}
		else
			return true;
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

	// escribir sol
	if (t.esSBT())
		std::cout << "SI" << std::endl;
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