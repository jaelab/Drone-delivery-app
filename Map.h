#pragma once
#include "Automate.h"
#include "Neighbourhood.h"
#include "QuartierCompare.h"
#include <string>
#include <vector>
#include <set>

using namespace std;

class Map
{
public:

	Map();

	Map(set<string> banqueQuartier);

	~Map();

	set<Neighbourhood*, QuartierCompare> getQuartiers() const;

	vector<Drone*> getDrones1();

	vector<Drone*> getDrones2();
	
	vector<Drone*> findDronesAvailable(vector<Drone*>& drones);

	Neighbourhood* findNeighbourhood(const string& code);

	void actualiserQuartier();

	void equilibrerFlotte();
	

private:
	set<Neighbourhood*, QuartierCompare> quartiers_;
	vector<Drone*> dronesType1_;
	vector<Drone*> dronesType2_;
};