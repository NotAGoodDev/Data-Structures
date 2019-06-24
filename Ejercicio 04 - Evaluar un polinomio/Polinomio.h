#ifndef POLINOMIO_H
#define POLINOMIO_H

#include <vector>
#include <math.h>

class Polinomio
{

public:
	int coef, exp;

	Polinomio(){}
	Polinomio(int c, int e) : coef(c), exp(e){}

	void operator+(Polinomio const& p)
	{
		this->coef += p.coef;
	}

private:

};

inline int resultadoMonomio(Polinomio const& p, int const& num)
{
	return p.coef * pow(num, p.exp);
}


#endif // !POLINOMIO_H
