// Nombre del alumno Álvaro David Ortiz Marchut
// Usuario del Juez E38


#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <set>
#include <string>
using nombre = std::string;
using profesor = nombre;
using alumno = nombre;
using puntos = int;
using listaAlumnos = std::set<alumno>;
using listaAlumnosPuntuacion = std::unordered_map<alumno, puntos>;
using listaAlumnosProfesores = std::unordered_map<alumno, profesor>;
using umProfesores = std::unordered_map<profesor, listaAlumnosPuntuacion>;

class autoescuela
{
private:
	const int MIN_PUNTUACION = 0;
	umProfesores profes;
	listaAlumnosProfesores lap;
public:
	autoescuela(){}

	//Coste constante O(1) respecto al numero de alumnos y profesores, dado que es unordered_map
	void alta(alumno const& A, profesor const& P)
	{
		if (lap.count(A) == 0)	//No se ha encontrado el alumno
		{
			lap[A] = P;
			profes[P][A] = MIN_PUNTUACION;
		}
		else	//Existe, entonces se le cambia de profesor
		{
			if (lap[A] != P)	//Si son distintos, no se le cambia
			{
				profesor pAntiguo = lap[A];	//Se guarda el profesor antiguo como aux
				lap[A] = P;	//El alumno cambia de profesor

				puntos punt = profes[pAntiguo][A];	//Se guarda la puntuacion
				profes[pAntiguo].erase(A);	//Borramos el alumno que se ha cambiado
				profes[P][A] = punt;	//Se asigna su anterior puntuacion
			}
		}
	}

	//Coste constante O(1) respecto al numero de alumnos dado que es unordered_map
	bool es_alumno(alumno const& A, profesor const& P)
	{
		return (lap[A] == P);	//Si coincide el profesor con el parametro P
	}


	//Coste constante O(1) respecto al numero de alumnos y profesores, dado que es unordered_map
	int puntuacion(alumno const& A)
	{
		if (lap.count(A) == 0)
			throw std::domain_error("El alumno A no esta matriculado");

		profesor aux = lap[A];
		return profes[aux][A];
	}

	//Coste constante O(1) respecto al numero de alumnos y profesores, dado que es unordered_map
	void actualizar(alumno const& A, puntos const& N)
	{
		if(lap.count(A) == 0)
			throw std::domain_error("El alumno A no esta matriculado");

		profesor aux = lap[A];	//Averiguamos el profesor del alumno
		profes[aux][A] += N;
	}

	//Coste lineal O(n) dado que tenemos que acceder a dos unordered_map
	//y ademas insertar datos ordenados en un set
	listaAlumnos examen(profesor const& P, puntos const& N)
	{
		listaAlumnos lAlumnosExamen;
		auto it = profes[P].begin();
		while (it != profes[P].end())
		{
			if (it->second >= N)
				lAlumnosExamen.insert(it->first);

			it++;
		}

		return lAlumnosExamen;
	}

	//Coste constante O(1) respecto al numero de alumnos y profesores, dado que es unordered_map
	void aprobar(alumno const& A)
	{
		if(lap.count(A) == 0)
			throw std::domain_error("El alumno A no esta matriculado");

		profesor aux = lap[A];
		lap.erase(A);
		profes[aux].erase(A);
	}

};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	std::string operacion;
	std::cin >> operacion;

	if (!std::cin)
		return false;

	autoescuela ae;
	
	while (operacion != "FIN")
	{
		try
		{
			if (operacion == "alta")
			{
				alumno a;
				profesor p;
				std::cin >> a >> p;
				ae.alta(a, p);
			}
			else if (operacion == "es_alumno")
			{
				alumno a;
				profesor p;
				std::cin >> a >> p;
				if (ae.es_alumno(a, p))
					std::cout << a << " es alumno de " << p << std::endl;
				else
					std::cout << a << " no es alumno de " << p << std::endl;
			}
			else if (operacion == "puntuacion")
			{
				alumno a;
				std::cin >> a;
				std::cout << "Puntuacion de " << a << ": " << ae.puntuacion(a) << std::endl;
			}
			else if (operacion == "actualizar")
			{
				alumno a;
				puntos p;
				std::cin >> a >> p;
				ae.actualizar(a, p);
			}
			else if (operacion == "examen")
			{
				profesor prof;
				puntos p;
				std::cin >> prof >> p;
				listaAlumnos la = ae.examen(prof, p);
				std::cout << "Alumnos de " << prof << " a examen:" << std::endl;

				auto it = la.begin();
				while (it != la.end())
				{
					std::cout << it->data() << std::endl;
					it++;
				}
			}
			else if (operacion == "aprobar")
			{
				alumno a;
				std::cin >> a;
				ae.aprobar(a);
			}
		}
		catch (const std::domain_error& e)
		{
			std::cout << "ERROR" << std::endl;
		}

		std::cin.ignore();	//Salto
		std::cin >> operacion;
	}


	std::cout << "------" << std::endl;
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