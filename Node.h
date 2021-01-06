#pragma once

#include <string>
#include <vector>

using namespace std;

class Node
{
public:

	Node();

	Node(const string& symbole);

	Node(const Node& node);

	~Node();

	string getSymbole() const;

	vector<Node*> getChilds() const;

	Node& ajouterEnfant(Node child);

	Node* findChild(const string& symbole);

	Node& operator=(const Node& node);

private:
	string symbole_;
	vector<Node*> childs_;

};