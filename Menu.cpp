#include "Menu.h"


using namespace std;

Menu::Menu()
{
	this->finiteStateMachine_ = nullptr;
	this->map_ = nullptr;
	this->manager_ = nullptr;
}

Menu::~Menu()
{
}

void Menu::afficherMenu() {
	cout << "(a) Create Finite state machine" << endl
		<< "(b) Handle Requests" << endl
		<< "(c) Show Statistics" << endl
		<< "(d) Exit " << endl;

		string entre;
		cin >> entre;

		if (entre == "a") {

			cout << "Enter the file name containing postal codes : ";
			string nomFichier;
			cin >> nomFichier;

			this->finiteStateMachine_ = new Automate();
			bool reussite = finiteStateMachine_->creerArbreAdresse(nomFichier);

			if (reussite) {
				this->map_ = new Map(this->finiteStateMachine_->getBanque());
				this->manager_ = new  RequestManager(*this->finiteStateMachine_, *this->map_);
				this->map_->equilibrerFlotte();
				cout << "Success! FSM was created." << endl;
			}

			else {
				this->finiteStateMachine_ = nullptr;
			}

			afficherMenu();
		}


		else if (entre == "b") {

			if (this->finiteStateMachine_ != nullptr) {
				cout << "Enter the file name containing requests : ";
				string nomFichier;
				cin >> nomFichier;

				bool reussite = this->manager_->assignRequests(nomFichier);
			}

			else {
				cout << "Error! Was not able to handle your requests." << endl;
			}
			
			afficherMenu();
		}

		else if (entre == "c") {
			cout << "Amount of requests handled: " << this->manager_->getRequestNumber() << endl;
			cout << "Amount of invalid requests given : " << this->manager_->getInvalidRequestNumber() << endl;
			afficherMenu();
		}

		else if (entre == "d")
			return;

	else {
		cout << "Invalid index, please try again." << endl << endl;
		afficherMenu();
	}
}
