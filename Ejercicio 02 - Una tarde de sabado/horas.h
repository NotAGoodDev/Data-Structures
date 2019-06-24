#ifndef HORAS_H
#define HORAS_H

class horas
{
public:

	int hora, minuto, segundo;
	horas() {}
	horas(int h, int m, int s) : hora(h), minuto(m), segundo(s) {}

	bool operator<(horas const& h)
	{
		if (this->hora < h.hora)
			return true;
		else if (this->hora == h.hora
			&& this->minuto < h.minuto)
			return true;
		else if (this->hora == h.hora
			&& this->minuto == h.minuto
			&& this->segundo < h.segundo)
			return true;
		else
			return false;
	}

	bool operator==(horas const& h)
	{
		return this->hora == h.hora
			&& this->minuto == h.minuto
			&& this->segundo == h.segundo;
	}

	horas operator+(horas const& h)
	{
		horas aux = *this;
		aux.segundo = aux.segundo + h.segundo;

		if (acarreoMinSeg(aux.segundo))
		{
			aux.segundo -= 60;
			aux.minuto++;
		}

		aux.minuto = aux.minuto + h.minuto;
		if (acarreoMinSeg(aux.minuto))
		{
			aux.minuto -= 60;
			aux.hora++;
		}

		aux.hora = aux.hora + h.hora;

		return aux;
	}

	/*
	bool masDeMedianoche()
	{
		return this->hora > 23;
	}
	*/
private:
	bool acarreoMinSeg(int const& t)
	{
		return t >= 60;
	}
};

#endif // !HORAS_H