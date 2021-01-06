#include "Request.h"

Request::Request()
{
}

Request::Request(Neighbourhood* QuartierDepart, Neighbourhood* QuartierFin, int weight)
	:QuartierDepart_(QuartierDepart), QuartierFin_(QuartierFin), weight_(weight)
{
}

Request::~Request()
{
}

Neighbourhood* Request::getQuartierDepart() const
{
	return QuartierDepart_;
}

Neighbourhood* Request::getQuartierFin() const
{
	return QuartierFin_;
}

int Request::getWeight() const
{
	return weight_;
}

bool Request::operator==(const Request requete)
{
	bool sontDeMemeDepart = this->getQuartierDepart() == requete.getQuartierDepart();
	bool sontDeMemeFin = this->getQuartierFin() == requete.getQuartierFin();

	return sontDeMemeDepart && sontDeMemeFin;
}