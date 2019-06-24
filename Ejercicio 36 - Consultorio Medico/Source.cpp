// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38



#include <string>
#include <sstream>
#include <exception>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>

using nombre = std::string;
using operacion = std::string;


class fecha
{
private:
	int dia;
	int hora;
	int minuto;
public:


	fecha() {}
	fecha(int d, int h, int m) : dia(d), hora(h), minuto(m) {}

	int getDia()
	{
		return dia;
	}

	int getHora()
	{
		return hora;
	}

	int getMinuto()
	{
		return minuto;
	}

	bool operator<(fecha f) const
	{
		if (this->dia < f.getDia())	//5 < 7
			return true;
		else if (this->dia == f.getDia() // 5 10 < 5 14
			&& this->hora < f.getHora())
			return true;
		else if (this->dia == f.getDia()	//5 10 20 < 5 10 40
			&& this->hora == f.getHora()
			&& this->minuto < f.getMinuto())
			return true;

		return false;
	}

	bool operator==(fecha & f) const
	{
		return (this->dia == f.getDia()
			&& this->hora == f.getHora()
			&& this->minuto == f.getMinuto());
	}
};

using listaMedicos = std::unordered_map<nombre, bool>;
using listaPacientes = std::unordered_map<nombre, bool>;
using listaConsultas = std::map<fecha, nombre>;
using listasMedicoConsultas = std::unordered_map<nombre, listaConsultas>;

struct tMedico
{
	nombre n;
	fecha f;

	tMedico() {}
	tMedico(nombre nom, fecha fec) : n(nom), f(fec) {}
};

struct tPaciente
{
	nombre n;
	fecha f;

	tPaciente() {}
	tPaciente(nombre nom, fecha fec) : n(nom), f(fec) {}
};
using vPacientes = std::vector<tPaciente>;

class consultorio
{
public:


	void nuevoMedico(nombre const& m) {
		lm[m] = true;
	}


	void pideConsulta(nombre const& p, nombre const& m, fecha const& f) {
		if (!lm[m])
			throw std::domain_error("Medico no existente");
		else if (lmc[m][f] != "")
			throw std::domain_error("Fecha ocupada");	//!

		lmc[m][f] = p;
	}


	nombre siguientePaciente(nombre const& m) {
		if (!lm[m])
			throw std::domain_error("Medico no existente");

		auto it = lmc[m].begin();

		if (it == lmc[m].end())
			throw std::domain_error("No hay pacientes");

		return it->second;
	}

	void atiendeConsulta(nombre const& m) {

		if (!lm[m])
			throw std::domain_error("Medico no existente");

		auto it = lmc[m].begin();

		if (it == lmc[m].end())
			throw std::domain_error("No hay pacientes");

		fecha f = it->first;	//Cogemos la fecha del primero de la lista

		lmc[m].erase(f);	//Y borramos la consulta en la fecha

	}

	vPacientes listaPacientes(nombre const& m, int const& dia) {

		if (!lm[m])
			throw std::domain_error("Medico no existente");

		vPacientes vP;
		auto it = lmc[m].begin();
		bool sobrepasaDia = false;

		while (it != lmc[m].end() && !sobrepasaDia)
		{
			fecha f = it->first;
			if (f.getDia() == dia)
			{
				nombre p = it->second;
				tPaciente paciente = tPaciente(p, f);
				vP.push_back(paciente);
			}
			else if (f.getDia() > dia)
				sobrepasaDia = true;

			it++;
		}

		return vP;
	}


private:
	listaMedicos lm;
	listasMedicoConsultas lmc;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada

	int nOperaciones;
	std::cin >> nOperaciones;

	if (!std::cin)
		return false;

	std::string linea;
	std::getline(std::cin, linea);
	consultorio c;

	for (int i = 0; i < nOperaciones; i++)
	{
		operacion o;
		std::getline(std::cin, linea);
		std::stringstream ss(linea);

		ss >> o;

		try
		{
			if (o == "nuevoMedico")
			{
				nombre m;
				ss >> m;
				c.nuevoMedico(m);
			}
			else if (o == "pideConsulta")
			{
				int dAux, hAux, mAux;
				nombre p, m;
				ss >> p >> m >> dAux >> hAux >> mAux;
				fecha f = fecha(dAux, hAux, mAux);
				c.pideConsulta(p, m, f);
			}
			else if (o == "listaPacientes")
			{
				nombre m;
				int d;
				ss >> m >> d;
				vPacientes lista = c.listaPacientes(m, d);
				std::cout << "Doctor " << m << " dia " << d << std::endl;
				for (int i = 0; i < lista.size(); i++)
				{
					tPaciente p = lista[i];
					if (p.f.getMinuto() < 10 && p.f.getHora() < 10)
						std::cout << p.n << " 0" << p.f.getHora() << ":0" << p.f.getMinuto() << std::endl;
					else if (p.f.getHora() < 10)
						std::cout << p.n << " 0" << p.f.getHora() << ":" << p.f.getMinuto() << std::endl;
					else if (p.f.getMinuto() < 10)
						std::cout << p.n << " " << p.f.getHora() << ":0" << p.f.getMinuto() << std::endl;
					else
						std::cout << p.n << " " << p.f.getHora() << ":" << p.f.getMinuto() << std::endl;
				}

				std::cout << "---" << std::endl;
			}
			else if (o == "siguientePaciente")
			{
				nombre m;
				ss >> m;
				nombre paciente = c.siguientePaciente(m);
				std::cout << "Siguiente paciente doctor " << m << std::endl
					<< paciente << std::endl;
				std::cout << "---" << std::endl;
			}
			else if (o == "atiendeConsulta")
			{
				nombre m;
				ss >> m;
				c.atiendeConsulta(m);
			}
		}
		catch (const std::domain_error& e)
		{
			std::cout << e.what() << std::endl;
			std::cout << "---" << std::endl;
		}
	}


	std::cout << "------" << std::endl;	//6 guiones

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