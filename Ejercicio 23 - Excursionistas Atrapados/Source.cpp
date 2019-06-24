// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
struct tExc
{
	int nEquipos;
	int n;
	tExc() { nEquipos = -1; n = -1; }
	tExc(int const& e, int const& m) : nEquipos(e), n(m){}
};

template <class T>
class bintree_ext : public bintree<T>
{
private:
	using Link = typename bintree<T>::Link;

	tExc excursionistas_rec(Link const& l)
	{
		if (l->left != nullptr
			&& l->right != nullptr)	//No nulo
		{
			tExc left = excursionistas_rec(l->left);
			tExc right = excursionistas_rec(l->right);
			
			if (left.nEquipos == 0 && right.nEquipos == 0 && l->elem > 0)
				return { left.nEquipos + right.nEquipos + 1, std::max(left.n, right.n) + l->elem};
			else
				return { left.nEquipos + right.nEquipos, std::max(left.n, right.n) + l->elem };
		}
		else if (l->left != nullptr)
		{
			tExc exc = excursionistas_rec(l->left);
			if (exc.nEquipos == 0 && l->elem > 0)
				exc.nEquipos = 1;
			return {exc.nEquipos, exc.n + l->elem };
		}
		else if (l->right != nullptr)
		{
			tExc exc = excursionistas_rec(l->right);
			if (exc.nEquipos == 0 && l->elem > 0)
				exc.nEquipos = 1;
			return { exc.nEquipos, exc.n + l->elem };
		}
		else
			if (l->elem > 0)
				return { 1, l->elem };
			else
				return { 0, 0 };

	}

public:
	bintree_ext<T>(){}
	bintree_ext<T>(bintree_ext<T> const& l, T const& e, bintree_ext<T> const& r) : bintree<T>(l, e, r){}

	// función que resuelve el problema
	tExc excursionistas()
	{
		if (this->raiz != nullptr)
		{
			tExc e = excursionistas_rec(this->raiz);
			return e;
		}
		else
			return { 0, 0 };
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

std::ostream& operator<< (std::ostream &out, tExc const& s)
{
	out << s.nEquipos << " " << s.n;
	return out;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	bintree_ext<int> t = leerArbol_ext(-1);

	// escribir sol
	std::cout << t.excursionistas() << std::endl;

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