#include <cmath>
class complejo
{
public:
	float real, imag;
	//Clase generica
	complejo(){}
	complejo(float x, float y) : real(x), imag(y){}

	complejo operator+(complejo const& c)
	{
		complejo aux;
		aux.real = this->real + c.real;
		aux.imag = this->imag + c.imag;

		return aux;
	}

	complejo operator*(complejo const& c)
	{
		complejo aux;
		aux.real = (this->real * c.real - this->imag * c.imag);
		aux.imag = (this->real * c.imag + c.real * this->imag);

		return aux;
	}

	float calculaModulo()
	{
		return sqrt((this->real * this->real) + (this->imag * this->imag));
	}

private:

};