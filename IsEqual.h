#pragma once
#include <string>
#include "Request.h"

using namespace std;

class IsEqual
{
public:

	IsEqual() {};

	IsEqual(Request* requete) { this->requete_ = requete; };

	~IsEqual() {};

	bool operator()(Request* requete) { return *this->requete_ == *requete; };

private:
	Request* requete_;
};