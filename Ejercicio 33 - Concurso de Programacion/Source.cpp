// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>
#include <algorithm>

using equipo = std::string;
using problema = std::string;
using minutos = int;
using veredicto = std::string;
using resueltos = int;

using problemaTiempo = std::unordered_map<problema, minutos>;
using tiempoResolucion = std::unordered_map<equipo, problemaTiempo>;

using estaResuelto = std::unordered_map<problema, bool>;
using problemasResueltos = std::map<equipo, estaResuelto>;

using solucion = std::unordered_map<equipo, minutos>;
using equipoResueltos = std::map<equipo, resueltos>;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	// leer los datos de la entrada
	problemasResueltos pr;
	tiempoResolucion t;
	equipoResueltos r;
	solucion s;
	std::string aux;
	std::getline(std::cin, aux);
	std::getline(std::cin, aux);
	std::stringstream ss(aux);

	equipo e;
	ss >> e;

	while (e != "FIN")
	{
		problema p;
		minutos m;
		veredicto v;
		ss >> e >> p >> m >> v;

		auto it = pr.find(e);
		if (it != pr.end())	//Existe
		{
			if (v == "AC")
			{
				if (!pr[e][p])	//No habian acertado el problema
				{
					pr[e][p] = true;	//Un problema resuelto mas
					auto it2 = t[e].find(p);

					if (it2 != t[e].end()) //Si han fallado en mas ocasiones
						s[e] = s[e] + t[e][p];

					s[e] = s[e] + m;	//Se le suman los minutos
					r[e]++;
				}
			}
			else
			{
				auto it2 = t[e].find(p);

				if (it2 != t[e].end()) //Si han fallado en mas ocasiones
					t[e][p] += 20;	//Tiempo resolucion + penalizacion
				else
					t[e][p] = 20;	//Primer fallo
			}
		}
		else //No existe
		{
			if (v == "AC")	//Han acertado
			{
				pr[e][p] = true;	//Lo han resuelto
				r[e]++;
				s[e] = m;	//No estaba dado de alta, no tiene penalizacion
			}
			else
			{
				t[e][p] = 20;	//No existia, y no tiene penalizacion
			}
		}

		std::getline(std::cin, aux);
		ss = std::stringstream(aux);
		ss >> e;
	}

	std::sort(r[e].begin(), r[e].end());
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