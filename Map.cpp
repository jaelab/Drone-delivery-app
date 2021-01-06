#include "Map.h"

Map::Map()
	:dronesType1_(10, nullptr), dronesType2_(5, nullptr) 
{
	//Drone creation
	for (unsigned int i = 0; i < dronesType1_.size(); i++)
		dronesType1_[i] = new Drone("faible");

	for (unsigned int j = 0; j < dronesType2_.size(); j++)
		dronesType2_[j] = new Drone("fort");
}

Map::Map(set<string> banqueQuartier)
	:dronesType1_(10, nullptr), dronesType2_(5, nullptr)
{
	for (unsigned int i = 0; i < dronesType1_.size(); i++)
		dronesType1_[i] = new Drone("faible");

	for (unsigned int j = 0; j < dronesType2_.size(); j++)
		dronesType2_[j] = new Drone("fort");

	for each (string address in banqueQuartier)
	{
		this->quartiers_.insert(new Neighbourhood(address));
	}

}

Map::~Map()
{
}

set<Neighbourhood*, QuartierCompare> Map::getQuartiers() const
{
	return this->quartiers_;
}

vector<Drone*> Map::getDrones1()
{
	return dronesType1_;
}

vector<Drone*> Map::getDrones2()
{
	return dronesType2_;
}

vector<Drone*> Map::findDronesAvailable(vector<Drone*>& drones)
{
	vector<Drone*> dronesAvailable;
	for each (Drone* drone in drones)
	{
		if (drone->getIsAvailable()) {
			dronesAvailable.push_back(drone);
		}

		else {
			drone->setCycleUnavailable(drone->getCycleUnavailable() - 1);
		}
	}

	return dronesAvailable;
}

Neighbourhood* Map::findNeighbourhood(const string& code)
{
	for(Neighbourhood* neighbourhood : this->quartiers_){
		if (neighbourhood->getCode() == code)
			return neighbourhood;
	}

	return nullptr;
}

void Map::actualiserQuartier()
{
	set<Neighbourhood*, QuartierCompare> quartiersActualiser;
	for each (Neighbourhood* neighbourhood in this->quartiers_)
		quartiersActualiser.insert(neighbourhood);

	this->quartiers_ = quartiersActualiser;
}

void Map::equilibrerFlotte()
{
	vector<Drone*> dronesDisponibleType1 = this->findDronesAvailable(this->dronesType1_);
	vector<Drone*> dronesDisponibleType2 = this->findDronesAvailable(this->dronesType2_);

	this->actualiserQuartier();

	for each (Neighbourhood* neighbourhood in this->quartiers_)
	{
		//Drone type 2
		while (neighbourhood->getNbDroneType2Necessaire() != 0 && !dronesDisponibleType2.empty()) {
			neighbourhood->setNbDroneType2Necessaire(neighbourhood->getNbDroneType2Necessaire() - 1);
			neighbourhood->setNbVisiteDrone(neighbourhood->getNbVisiteDrone() + 1);
			neighbourhood->ajouterUnDrone(dronesDisponibleType2.back());
			dronesDisponibleType2.pop_back();
		}

		//Drone type 1
		while (neighbourhood->getNbDroneType1Necessaire() != 0 && !dronesDisponibleType1.empty()) {
			neighbourhood->setNbDroneType1Necessaire(neighbourhood->getNbDroneType1Necessaire() - 1);
			neighbourhood->setNbVisiteDrone(neighbourhood->getNbVisiteDrone() + 1);
			neighbourhood->ajouterUnDrone(dronesDisponibleType1.back());
			dronesDisponibleType1.pop_back();
		}
	}

	if (!dronesDisponibleType1.empty() || !dronesDisponibleType2.empty()) {
		this->actualiserQuartier();

		set<Neighbourhood*, QuartierCompare>::iterator it = this->quartiers_.begin();

		while (!dronesDisponibleType2.empty()) {
			(*it)->setNbVisiteDrone((*it)->getNbVisiteDrone() + 1);
			(*it)->ajouterUnDrone(dronesDisponibleType2.back());
			dronesDisponibleType2.pop_back();
			++it;
		}
		while (!dronesDisponibleType1.empty()) {
			(*it)->setNbVisiteDrone((*it)->getNbVisiteDrone() + 1);
			(*it)->ajouterUnDrone(dronesDisponibleType1.back());
			dronesDisponibleType1.pop_back();
			++it;
		}
	}
}