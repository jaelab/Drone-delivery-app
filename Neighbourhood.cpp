#include "Neighbourhood.h"

Neighbourhood::Neighbourhood()
	:code_(""), droneVisitCount(0), droneType1Count(0), nbDroneType2Necessaire_(0)
{
}

Neighbourhood::Neighbourhood(const string& code)
	: code_(code), droneVisitCount(0), droneType1Count(0), nbDroneType2Necessaire_(0)
{
}

Neighbourhood::~Neighbourhood()
{
}

string Neighbourhood::getCode() const
{
	return this->code_;
}

void Neighbourhood::setCode(const string& code)
{
	this->code_ = code;
}

unsigned int Neighbourhood::getNbVisiteDrone() const
{
	return this->droneVisitCount;
}

void Neighbourhood::setNbVisiteDrone(const unsigned int& nbVisiteDrone)
{
	this->droneVisitCount = nbVisiteDrone;
}

unsigned int Neighbourhood::getNbDroneType1Necessaire() const
{
	return this->droneType1Count;
}

void Neighbourhood::setNbDroneType1Necessaire(const unsigned int& nbDroneType1Necessaire)
{
	this->droneType1Count = nbDroneType1Necessaire;
}

unsigned int Neighbourhood::getNbDroneType2Necessaire() const
{
	return this->nbDroneType2Necessaire_;
}

void Neighbourhood::setNbDroneType2Necessaire(const unsigned int& nbDroneType2Necessaire)
{
	this->nbDroneType2Necessaire_ = nbDroneType2Necessaire;
}

vector<Drone*> Neighbourhood::getDronesPresents() const
{
	return this->presentDrones;
}

void Neighbourhood::setDronesPresents(const vector<Drone*>& dronesPresents)
{
	this->presentDrones = dronesPresents;
}

void Neighbourhood::ajouterUnDrone(Drone* drone)
{
	presentDrones.push_back(drone);
}


bool operator<(const Neighbourhood& neighbourhood1, const Neighbourhood& neighbourhood2)
{
	if (neighbourhood1.droneType1Count + neighbourhood1.nbDroneType2Necessaire_ < neighbourhood2.droneType1Count + neighbourhood2.nbDroneType2Necessaire_)
		return false;

	else if (neighbourhood1.droneType1Count + neighbourhood1.nbDroneType2Necessaire_ > neighbourhood2.droneType1Count + neighbourhood2.nbDroneType2Necessaire_)
		return true;

	else {

		if (neighbourhood1.droneVisitCount < neighbourhood2.droneVisitCount)
			return true;

		else if (neighbourhood1.droneVisitCount > neighbourhood2.droneVisitCount)
			return false;

		else
			return neighbourhood1.code_ < neighbourhood2.code_;
	}
}

bool Neighbourhood::operator==(const Neighbourhood* neighbourhood)
{
	return this->code_ == neighbourhood->code_;
}
