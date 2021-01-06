#pragma once
class Drone;
#include "Drone.h"
#include <string>
#include <vector>

using namespace std;

class Neighbourhood
{
public:

	Neighbourhood();

	Neighbourhood(const string& code);

	~Neighbourhood();

	string getCode() const;

	void setCode(const string& code);

	unsigned int getNbVisiteDrone() const;

	void setNbVisiteDrone(const unsigned int& nbVisiteDrone);

	unsigned int getNbDroneType1Necessaire() const;

	void setNbDroneType1Necessaire(const unsigned int& nbDroneType1Necessaire);

	unsigned int getNbDroneType2Necessaire() const;

	void setNbDroneType2Necessaire(const unsigned int& nbDroneType2Necessaire);

	vector<Drone*> getDronesPresents() const;

	void setDronesPresents(const vector<Drone*>& dronesPresents);


	void ajouterUnDrone(Drone* drone);

	
	friend bool operator<(const Neighbourhood& neighbourhood1, const Neighbourhood& neighbourhood2);

	bool operator==(const Neighbourhood* neighbourhood);

private:
	string code_;
	unsigned int droneVisitCount;
	unsigned int droneType1Count;
	unsigned int nbDroneType2Necessaire_;
	vector<Drone*> presentDrones;
};