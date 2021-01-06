#include "FiniteStateMachine.h"

FiniteStateMachine::FiniteStateMachine()
	: startingState_("")
{
}

FiniteStateMachine::~FiniteStateMachine()
{
}

Node FiniteStateMachine::getStartingState() const
{
	return startingState_;
}

void FiniteStateMachine::setStartingState(const Node& symbol)
{
	this->startingState_ = symbol;
}

set<string> FiniteStateMachine::getBanque()
{
	return this->banqueQuartiers_;
}

pair<bool, Node*> FiniteStateMachine::findState(const string& symbol)
{
	return this->findState(symbol, symbol.substr(0, 1), &this->startingState_);
}

pair<bool, Node*> FiniteStateMachine::findState(const string& symbol, const string& actualsymbol, Node* state)
{
	Node* nextState = state->findChild(actualsymbol);

	//On a atteint la fin de l'finiteStateMachine -> retoune false avec le dernier état visité
	if (nextState == nullptr)
		return make_pair(false, state);

	//Le symbol est trouvé -> retoune true avec son état associé
	else if (nextState->getsymbol() == symbol)
		return make_pair(true, nextState);
	
	//On continue le parcours dans l'finiteStateMachine
	else
		return findState(symbol, symbol.substr(0, actualsymbol.size() + 1), nextState);
}


void FiniteStateMachine::createStates(const string& symbol)
{
	pair<bool, Node*> postalCode;
	int unsigned size = 0;
	while(size < symbol.size()){
		postalCode = this->findState(symbol);
		size = postalCode.second->getsymbol().size() + 1;
		if (!postalCode.first)
			postalCode.second->ajouterEnfant(Node(symbol.substr(0, size)));
	}
}

bool FiniteStateMachine::creerArbreAdresse(const string& file)
{
	ifstream fileIn;
	fileIn.open(file);

	//Fichier non trouver
	if (fileIn.fail()) {
		cout << "Failed to open file." << endl;
		return false;
	}

	string address;
	while (!fileIn.eof()) {
		getline(fileIn, address);
		banqueQuartiers_.insert(address);
		this->createStates(address);
	}

	return true;
}
