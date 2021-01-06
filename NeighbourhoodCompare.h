#pragma once
#include <string>
#include "Neighbourhood.h"

using namespace std;

class QuartierCompare
{
public:

	bool operator()(const Neighbourhood* neighbourhood1, const Neighbourhood* neighbourhood2) { return *neighbourhood1 < *neighbourhood2; };
};