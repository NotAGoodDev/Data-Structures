// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Polinomio.h"

using vector = std::vector<int>;
using vectorPol = std::vector<Polinomio>;


// función que resuelve el problema

int resolverPolinomio(vectorPol const& v, int const& num)
{
	int total = 0;
	for (int i = 0; i < v.size(); i++)
		total += resultadoMonomio(v[i], num);

	return total;
}

void resolver(vectorPol const& vP, vector const& v) {
	for (int i = 0; i < v.size(); i++)
		std::cout << resolverPolinomio(vP, v[i]) << " ";
	std::cout << std::endl;
}

int buscarPosicion(vectorPol &vP, Polinomio const& p)
{
	int i = 0;
	if(vP.size() > 0)
		while (i < vP.size() && p.exp < vP[i].exp)	//Si ha llegado al final o es menor
			i++;

	return i;
}

void moverPolinomio(vectorPol &vP, int const& ini)
{
	vP.push_back(Polinomio());	//Nueva posicion
	for (int i = vP.size() - 1; i > ini; i--)	//Bucle para mover
		vP[i] = vP[i - 1];
}

void tratarPolinomio(vectorPol &vP, Polinomio const& p)
{
	int pos = buscarPosicion(vP, p);
	if (pos == vP.size())	//No se ha encontrado ningun exp menor
		vP.push_back(p);	//Aniadir el polinomio al final
	else if (vP[pos].exp == p.exp)
		vP[pos] + p;	//Suma de coeficientes, sobrecargada
	else if (p.exp > vP[pos].exp)
	{
		moverPolinomio(vP, pos);
		vP[pos] = p;
	}

}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada

	int coef, exp, n;
	std::cin >> coef >> exp;

	if (!std::cin)
		return false;

	vectorPol vP;

	do
	{
		if (coef != 0 || exp != 0)	//No es el final
			tratarPolinomio(vP, Polinomio(coef, exp));
		std::cin >> coef >> exp;
	} while (coef != 0 || exp != 0);

	std::cin >> n;
	vector v(n);	//Vector que lleva los N valores

	for (int i = 0; i < n; i++)
		std::cin >> v[i];

	resolver(vP, v);

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