#pragma once
class Request;
#include <string>
#include <deque>
#include "Request.h"
using namespace std;

class Drone
{
public:


	Drone();

	Drone(const string& type);

	~Drone();

	string getType() const;

	void setType(const string& type);

	unsigned int getWeigth() const;

	void setWeigth(const unsigned int& weigth);

	unsigned int getMaxWeigth() const;

	deque<Request*> getPackages() const;

	bool getIsAvailable() const;

	void setIsAvailable(const bool& isAvailable);

	int getCycleUnavailable() const;

	void setCycleUnavailable(const int& cycle);

	bool isLightEnough(const unsigned int& package);

	void addPackage(Request* package);

	void popFirstPackage();

private:
	string type_;
	string position_;
	unsigned int weigth_;
	unsigned int maxWeigth_;
	deque<Request*> packages_;
	bool isAvailable_;
	int cycleUnavailable_;
};