class horas
{
public:

	int hora, minuto, segundo;
	horas(){}
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

private:
};