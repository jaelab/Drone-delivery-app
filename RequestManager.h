#pragma once
#include "Automate.h"
#include "Drone.h"
#include "Request.h"
#include "Map.h"
#include "isEqual.h"
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

class RequestManager
{
public:

	RequestManager(Automate& automate, Map& map);

	~RequestManager();

	Automate& getAutomate() const;

	unsigned int getRequestNumber() const;

	void setRequestNumber(const unsigned int& number);

	unsigned int getInvalidRequestNumber() const;

	void setInvalidRequestNumber(const unsigned int& number);

	bool isEqual(pair<Node*, vector<Drone*>> pair, string destination);
	
	void refreshCycle();

	void assignPackages();

	bool assignRequests(const string& file) ;

	void evaluateNeed();

private:
	Automate& finiteStateMachine_;
	unsigned int requestNumber_;
	unsigned int invalidRequestNumber_;
	deque<Request*> listRequest_;
	Map& map_;
};
