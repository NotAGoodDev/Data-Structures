#include "carnet_puntos.h"

	void carnet_puntos::nuevo(std::string const& dni)
	{
		if (dp.count(dni) > 0)	//Si existe el conductor
			throw std::domain_error("Conductor duplicado");

		dp[dni] = PUNTOS_MAX;	//Puntos maximos
		nCeP[PUNTOS_MAX]++;
	}

	void carnet_puntos::quitar(std::string const& dni, int const& puntos)
	{
		if (dp.count(dni) == 0)	//Si no existe en la lista
			throw std::domain_error("Conductor inexistente");
	
		if (puntos >= PUNTOS_MIN)	//Si los puntos son positivos
		{
			nCeP[dp[dni]]--;	//Restamos 1 al num de conductores en puntos antiguo
			dp[dni] -= puntos;

			if (dp[dni] < PUNTOS_MIN)	//Si es menor que 0
				dp[dni] = PUNTOS_MIN;	//-> 0

			nCeP[dp[dni]]++;	//Sumamos 1 al num de conductores en puntos nuevo
		}
	}

	int carnet_puntos::consultar(std::string const& dni)
	{
		if (dp.count(dni) == 0)	//Si no existe en la lista
			throw std::domain_error("Conductor inexistente");

		return dp[dni];
	}

	int carnet_puntos::cuantos_con_puntos(int const& puntos)
	{
		if (puntos < PUNTOS_MIN || puntos > PUNTOS_MAX)
			throw std::domain_error("Puntos no validos");


		return nCeP[puntos];
	}

	/*void carnet_puntos::recuperar(std::string const& dni, int const& puntos) {
		if (!dp.count(dni) > 0)
			throw std::domain_error("Conductor inexistente");

		if (puntos >= PUNTOS_MIN)	//Si los puntos son positivos
		{
			dp[dni] += puntos;
			if (dp[dni] > PUNTOS_MAX)
				dp[dni] = PUNTOS_MAX;
		}
	}

	listaConductores carnet_puntos::lista_por_puntos(int const& puntos)
	{
		listaConductores aux;
		dni a = "abc";
		bool b = true;
		aux[a] = b;

		return aux;
	}
	*/