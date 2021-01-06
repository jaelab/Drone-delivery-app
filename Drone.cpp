#include "Drone.h"

Drone::Drone()
	: type_("faible"), weigth_(0), maxWeigth_(1), isAvailable_(true), cycleUnavailable_(0)
{
	this->packages_ = deque<Request*>(0);
}

Drone::Drone(const string& type)
	: type_(type), weigth_(0), isAvailable_(true), cycleUnavailable_(0)
{
	if (type == "faible")
		this->maxWeigth_ = 1000;

	else
		this->maxWeigth_ = 5000;

	this->packages_ = deque<Request*>(0);
}

Drone::~Drone()
{
}

string Drone::getType() const
{
	return this->type_;
}

void Drone::setType(const string& type)
{
	this->type_ = type;
}

unsigned int Drone::getWeigth() const
{
	return this->weigth_;
}

void Drone::setWeigth(const unsigned int& weigth)
{
	this->weigth_ = weigth;
}

unsigned int Drone::getMaxWeigth() const
{
	return this->maxWeigth_;
}

deque<Request*> Drone::getPackages() const
{
	return this->packages_;
}

bool Drone::getIsAvailable() const
{
	return this->isAvailable_;
}

void Drone::setIsAvailable(const bool& isAvailable)
{
	this->isAvailable_ = isAvailable;
}

int Drone::getCycleUnavailable() const
{
	return cycleUnavailable_;
}

void Drone::setCycleUnavailable(const int& cycle)
{
	cycleUnavailable_ = cycle;
}

bool Drone::isLightEnough(const unsigned int& package)
{
	if (weigth_ + package <= maxWeigth_)
		return true;

	return false;
}

void Drone::addPackage(Request* package)
{
	if (this->isLightEnough(package->getWeight())) {
		this->packages_.push_front(package);
		this->weigth_ += package->getWeight();
	}
}

void Drone::popFirstPackage()
{
	this->packages_.pop_front();
}