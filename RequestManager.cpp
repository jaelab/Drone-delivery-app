#include "RequestManager.h"

RequestManager::RequestManager(Automate& finiteStateMachine, Map& map)
	:finiteStateMachine_(finiteStateMachine), map_(map), requestNumber_(0), invalidRequestNumber_(0)
{
}

RequestManager::~RequestManager()
{
}

Automate& RequestManager::getAutomate() const 
{
	return finiteStateMachine_;
}

unsigned int RequestManager::getRequestNumber() const 
{
	return requestNumber_;
}

void RequestManager::setRequestNumber(const unsigned int& number) 
{
	requestNumber_ = number;
}

unsigned int RequestManager::getInvalidRequestNumber() const
{
	return invalidRequestNumber_;
}

void RequestManager::setInvalidRequestNumber(const unsigned int& number)
{
	invalidRequestNumber_ = number;
}

bool RequestManager::isEqual(pair<Node*, vector<Drone*>> pair, string destination)
{
		if (pair.first->getSymbole() == destination)
			return true;
		else
			return false;
}

void RequestManager::refreshCycle() 
{
	vector<Drone*>::iterator it1;
	for (auto it1 : map_.getDrones1()) {
		int cycle = it1->getCycleUnavailable();
		if (cycle > 0) {
			it1->setWeigth(it1->getWeigth() - it1->getPackages().back()->getWeight());
			it1->popFirstPackage();
			this->requestNumber_++;
			it1->setCycleUnavailable(cycle - 1);
			if (it1->getCycleUnavailable() == 0)
				it1->setIsAvailable(true);
		}
	}

	vector<Drone*>::iterator it2;
	for (auto it2 : map_.getDrones2()) {
		int cycle = it2->getCycleUnavailable();
		if (cycle > 0) {
			it2->setWeigth(it2->getWeigth() - it2->getPackages().back()->getWeight());
			it2->popFirstPackage();
			this->requestNumber_++;
			it2->setCycleUnavailable(cycle - 1);
			if (it2->getCycleUnavailable() == 0)
				it2->setIsAvailable(true);
		}
	}

	for (Neighbourhood* neighbourhood : this->map_.getQuartiers()) {
		neighbourhood->getDronesPresents().clear();
	}
}

void RequestManager::assignPackages() 
{
	int dimension = this->listRequest_.size();
	for (int i = 0; i < dimension; i++) {
		
		if (!this->listRequest_.back()->getStartNeighbourhood()->getDronesPresents().empty()) {
			for (Drone* drone : this->listRequest_.back()->getStartNeighbourhood()->getDronesPresents()) {
				
				if (drone->isLightEnough(this->listRequest_.back()->getWeight())) {

					if (!drone->getPackages().empty() && *drone->getPackages().at(0) == *this->listRequest_.back()) {
						drone->addPackage(this->listRequest_.back());
						drone->setCycleUnavailable(drone->getCycleUnavailable() + 1);
						drone->setIsAvailable(false);
						this->listRequest_.pop_back();
						break;
					}
					else if (drone->getPackages().empty()) {
						drone->addPackage(this->listRequest_.back());
						drone->setCycleUnavailable(drone->getCycleUnavailable() + 1);
						drone->setIsAvailable(false);
						this->listRequest_.pop_back();
						break;
					}
					else {
						continue;
					}
				}

				else {
					if (!drone->getPackages().empty() && drone->getType() == "faible" && drone->getPackages().at(0) == this->listRequest_.back()) {
						for (Request* requete : drone->getPackages()) {
							this->listRequest_.push_front(requete);
							drone->getPackages().pop_back();
							drone->setCycleUnavailable(drone->getCycleUnavailable() - 1);
						}
						drone->setIsAvailable(true);
					}

					else{
						listRequest_.push_front(listRequest_.back());
						listRequest_.pop_back();
					}
				}
			}	
		}

		else {
			listRequest_.push_front(listRequest_.back());
			listRequest_.pop_back();
		}
	}
}

bool RequestManager::assignRequests(const string& file)
{
	ifstream fileIn;
	fileIn.open(file);

	if (fileIn.fail()) {
		cout << "Failed to open file. Please check name and retry." << endl;
		return false;
	}

	string startingPoint;
	string endingPoint;
	int weight;
	while (!fileIn.eof()) {
		fileIn >> startingPoint >> endingPoint >> weight;
		if (startingPoint == endingPoint && finiteStateMachine_.findState(startingPoint).first)
			requestNumber_++;
		else if (finiteStateMachine_.findState(startingPoint).first && finiteStateMachine_.findState(endingPoint).first)
			listRequest_.push_front(new Request(this->map_.findNeighbourhood(startingPoint), this->map_.findNeighbourhood(endingPoint), weight));
		else
			invalidRequestNumber_++;
	}
	
	assignPackages();
	
	refreshCycle();
	
	evaluateNeed();

	map_.equilibrerFlotte(); 

	return true;
}

void RequestManager::evaluateNeed() {

	deque<Request*> listRequestSimple = this->listRequest_;
	vector<deque<Request*>> multipleRequestsList;
	vector<deque<Request*>::iterator> vectIterator;

	bool estAjouter = false;
	int i = 0;
	for (int j = 0; j < listRequestSimple.size(); j++) {
		IsEqual egal(listRequestSimple[j]);
		deque<Request*>::iterator requeteIdentique = listRequestSimple.begin() + j;
		while (requeteIdentique != listRequestSimple.end()) {

			requeteIdentique = find_if(requeteIdentique + 1, listRequestSimple.end(), egal);
			if (requeteIdentique != listRequestSimple.end()) {
				vectIterator.push_back(requeteIdentique);
				multipleRequestsList.resize(i + 1);
				multipleRequestsList[i].push_front(*requeteIdentique);
				estAjouter = true;
			}
		}

		if (estAjouter) {
			multipleRequestsList[i].push_front(*(listRequestSimple.begin() + j));
			vectIterator.push_back(listRequestSimple.begin() + j);
			estAjouter = false;
			i++;
			listRequestSimple.erase(vectIterator[0]);
			j--;
			vectIterator.clear();
		}
	}

	int totalWeight;
	for (unsigned int i = 0; i < multipleRequestsList.size(); i++) {
		totalWeight = 0;
		deque<Request*>::iterator it = multipleRequestsList[i].begin();

		for (it; it != multipleRequestsList[i].end(); ++it) {
			
			if (totalWeight > 5000) {
				it--;
				totalWeight -= (*it)->getWeight();
				(*it)->getStartNeighbourhood()->setNbDroneType2Necessaire((*it)->getStartNeighbourhood()->getNbDroneType2Necessaire() + 1);
				totalWeight = 0;
			}
			totalWeight += (*it)->getWeight();
		}

		if (totalWeight <= 1000) 
			multipleRequestsList[i].at(0)->getStartNeighbourhood()->setNbDroneType1Necessaire(multipleRequestsList[i].at(0)->getStartNeighbourhood()->getNbDroneType1Necessaire() + 1);

		else 
			multipleRequestsList[i].at(0)->getStartNeighbourhood()->setNbDroneType2Necessaire(multipleRequestsList[i].at(0)->getStartNeighbourhood()->getNbDroneType2Necessaire() + 1);	
	}

	for (unsigned int i = 0; i < listRequestSimple.size(); i++) {

		if (listRequestSimple[i]->getWeight() <= 1000)
			listRequestSimple[i]->getStartNeighbourhood()->setNbDroneType1Necessaire(listRequestSimple[i]->getStartNeighbourhood()->getNbDroneType1Necessaire() + 1);

		else
			listRequestSimple[i]->getStartNeighbourhood()->setNbDroneType2Necessaire(listRequestSimple[i]->getStartNeighbourhood()->getNbDroneType2Necessaire() + 1);
	}
}