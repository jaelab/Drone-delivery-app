#pragma once

#include "Automate.h"
#include "RequestManager.h"
#include <iostream>
#include <vector>

using namespace std;

class Menu
{
public:

	Menu();

	~Menu();

	void afficherMenu();

private:
	Automate* finiteStateMachine_;
	Map* map_;
	RequestManager* manager_;
};

