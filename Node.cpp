#include "Node.h"

Node::Node()
	: symbole_("")
{
	this->childs_ = vector<Node*>(0);
}

Node::Node(const string& symbole)
	: symbole_(symbole)
{
	this->childs_ = vector<Node*>(0);
}

Node::Node(const Node& node)
	: symbole_(node.symbole_), childs_(node.childs_)
{
}

Node::~Node()
{
}

string Node::getSymbole() const
{
	return this->symbole_;
}

vector<Node*> Node::getChilds() const
{
	return this->childs_;
}

Node& Node::ajouterEnfant(Node child)
{
	this->childs_.push_back(new Node(child));
	return *this->childs_.back();
}

Node* Node::findChild(const string& symbole)
{
	vector<Node*>::iterator child;
	for (auto child : this->childs_) {
		if (child->getSymbole() == symbole)
			return child;
	}

	return nullptr;
}

Node& Node::operator=(const Node& node)
{
	if (this != &node)
	{
		this->symbole_ = node.symbole_;
		this->childs_ = node.childs_;
	}
	return *this;
}