// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include "horas.h"

using vector = std::vector<horas>;

bool horaCorrecta(horas const& h)
{
	return (h.hora <= 23 && h.hora >= 0)
		&& (h.minuto <= 59 && h.minuto >= 0)
		&& (h.segundo <= 59 && h.segundo >= 0);
}

std::ostream& operator<<(std::ostream& out, horas h)
{

	out << std::setfill('0') << std::setw(2) << h.hora << ":"
		<< std::setfill('0') << std::setw(2) << h.minuto << ":"
		<< std::setfill('0') << std::setw(2) << h.segundo;


	return out << std::endl;
}

//Sobrecarga
std::istream& operator>> (std::istream &in, horas &h)
{
	
	char basura;	//Para leer los ':' 
	in >> h.hora >> basura >> h.minuto >> basura >> h.segundo;

	return in;
}

//Si el horario es correcto
void esValida(vector & vTrenes, vector & vHorario, int const& horario)
{
	if (horaCorrecta(vHorario[horario])) {
		int tren = 0;
		while (tren < vTrenes.size()	//Esquema de recorrido
			&& vTrenes[tren] < vHorario[horario])	//Busca que el tren no se pase del horario
			tren++;

		if (tren < vTrenes.size() && horaCorrecta(vTrenes[tren]))	//Si el esquema de recorrido no ha llegado al final y el tren tiene una hora correcta
			std::cout << vTrenes[tren];
		else	//En otro caso, no hay un horario bueno
			std::cout << "NO" << std::endl;
	}
	else
		throw std::invalid_argument("ERROR");	//Solo se lanza excepcion si no son validos

}

// función que resuelve el problema
void resolver(vector & vTrenes, vector & vHorario) {
	for (size_t horario = 0; horario < vHorario.size(); horario++) {
		try {
			esValida(vTrenes, vHorario, horario);
		} catch (std::invalid_argument &ia) {
			std::cout << ia.what() << std::endl;
		}
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso()
{
	// leer los datos de la entrada	
	int nTrenes, nHoras;
	std::cin >> nTrenes >> nHoras;

	if (nTrenes == 0
		&& nHoras == 0)
		return false;

	vector vT(nTrenes), vH(nHoras);
	for (int i = 0; i < nTrenes; i++)
		std::cin >> vT[i];

	for (int i = 0; i < nHoras; i++)
		std::cin >> vH[i];

	resolver(vT, vH);
	std::cout << "---" << std::endl;

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