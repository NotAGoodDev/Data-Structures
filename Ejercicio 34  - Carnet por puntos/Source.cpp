#include <iostream>
#include <string>
#include <fstream>

#include "carnet_puntos.h"


bool resuelveCaso() {
	std::string orden, dni;
	int punt;
	std::cin >> orden;
	if (!std::cin)
		return false;

	carnet_puntos dgt;

	while (orden != "FIN") {
		try {
			if (orden == "nuevo") {
				std::cin >> dni;
				dgt.nuevo(dni);
			}
			else if (orden == "quitar") {
				std::cin >> dni >> punt;
				dgt.quitar(dni, punt);
			}
			/*
			else if (orden == "recuperar") {
				std::cin >> dni >> punt;
				dgt.recuperar(dni, punt);
			}
			*/
			else if (orden == "consultar") { 
				std::cin >> dni;
				punt = dgt.consultar(dni);
				std::cout << "Puntos de " << dni << ": " << punt << '\n';
			}
			else if (orden == "cuantos_con_puntos") {
				std::cin >> punt;
				int cuantos = dgt.cuantos_con_puntos(punt);
				std::cout << "Con " << punt << " puntos hay " << cuantos << '\n';
			}
			/*
			else if (orden == "lista_por_puntos") {
				std::cin >> punt;
				auto const& lista = dgt.lista_por_puntos(punt);
				std::cout << "Tienen " << punt << " puntos:";
				
				for (auto it = lista.begin(); it != lista.end(); it++)
					std::cout << " " << it->first;

				std::cout << '\n';
			}
			*/
			else
				std::cout << "OPERACION DESCONOCIDA\n";
		}
		catch (std::domain_error e) {
			std::cout << "ERROR: " << e.what() << '\n';
		}
		std::cin >> orden;
	}
	std::cout << "---\n";
	return true;
}

int main() {

	// ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// restablecimiento de cin
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("pause");
#endif
	return 0;
}
