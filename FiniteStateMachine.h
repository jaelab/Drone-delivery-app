#pragma once

#include "Node.h"
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <set>

using namespace std;

class FiniteStateMachine
{
public:

	FiniteStateMachine();

	~FiniteStateMachine();


	Node getStartingState() const;

	void setStartingState(const Node& startingState);

	set<string> getBanque();

	pair<bool, Node*> findState(const string& symbol);

	pair<bool, Node*> findState(const string& symbol,const string& actualSymbol, Node* state);

	void createStates(const string& symbol);

	bool creerArbreAdresse(const string& fichier);

private:
	Node startingState_;
	set<string> banqueQuartiers_;
};