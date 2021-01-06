#pragma once
class Neighbourhood;
#include <string>
#include <vector>
#include "Neighbourhood.h"

using namespace std;

class Request
{
public:
	Request();
	Request(Neighbourhood* StartNeighbourhood, Neighbourhood* EndNeighbourhood, int weight);
	~Request();

	Neighbourhood* getStartNeighbourhood() const;
	Neighbourhood* getEndNeighbourhood() const;
	int getWeight() const;

	bool operator==(const Request requete2);

private:
	Neighbourhood* StartNeighbourhood_;
	Neighbourhood* EndNeighbourhood_;
	int weight_;
};