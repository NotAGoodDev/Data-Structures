#ifndef PERSONA_H
#define PERSONA_H

#include <string>

class persona
{
public:

	persona(){}
	persona(int e, std::string n) : edad(e), nombre(n) {}

	std::string getNombre()
	{
		return nombre;
	}

	int getEdad()
	{
		return edad;
	}

private:
	std::string nombre;
	int edad;
};

#endif // !PERSONA_H
