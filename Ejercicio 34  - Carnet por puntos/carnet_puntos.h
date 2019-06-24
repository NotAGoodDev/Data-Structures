//#ifndef CARNET_PUNTOS_H
//#define CARNET_PUNTOS_H

#include <string>
#include <unordered_map>
#include <vector>

int const PUNTOS_MAX = 15;
int const PUNTOS_MIN = 0;
using dni = std::string;
using puntos = int;
using dniPuntos = std::unordered_map<dni, puntos>;
using numDeConductoresEnPuntos = std::vector<int>;
class carnet_puntos
{
private:
	dniPuntos dp;
	numDeConductoresEnPuntos nCeP = numDeConductoresEnPuntos(PUNTOS_MAX + 1, 0);	//Vector de 0p a 15p con valor 0
public:

	//Todos los costes son O(1) con respecto al num de conductores
	//dado que dniPuntos es un mapa desordenado

	void nuevo(std::string const& dni);

	void quitar(std::string const& dni, int const& puntos);

	int consultar(std::string const& dni);

	int cuantos_con_puntos(int const& puntos);

	//void recuperar(std::string const& dni, int const& puntos);

	//listaConductores lista_por_puntos(int const& puntos);
};

//#endif // !CARNET_PUNTOS_H