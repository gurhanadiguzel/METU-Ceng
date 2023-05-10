#include "Node.h"

// // // THE FRIEND METHODS ARE ALREADY IMPLEMENTED BELOW. // // //
// // // // // // // DO NOT CHANGE THEM! // // // // // // //

Node::Node(int id) {
	// TODO
	this->id = id;
}

Node::~Node() {
	// TODO
	this->children.clear();
}

Node::Node(const Node& node) {
	// TODO
	this->id = node.id;
	this->children = node.children;
}

int Node::getId() const {
	// TODO
	return this->id;
}

char Node::getData() const {
	// TODO
	return this->getData();
	
}

vector<Node*>& Node::getChildren() {
	// TODO
	return this->children;
}

void Node::operator+=(Node& childNode) {
	// TODO
	for(int i=0; i < childNode.children.size();i++){
		this->children.push_back(childNode.children [i]);
	}	
}

Node* Node::operator&(const Node& node) const {
	// TODO
}

// This is already implemented for you, do NOT change it!
ostream& operator<<(ostream& os, const Node& node) {
	try {
		node.getData();
		os << *(DataNode*)&node;
	}
	catch (InvalidRequest e) {
		os << "[" << node.id;
		for (int i = 0; i < node.children.size(); i++)
			os << ", " << *node.children[i];
		os << "]";
		return os;
	}
}

/*************** DataNode *****************/

DataNode::DataNode(int id, char data) {
	// TODO
	this->id = id;
	this->data = data;
}

DataNode::~DataNode() {
	// TODO
	this->children.clear();
}

DataNode::DataNode(const DataNode& dataNode) {
	// TODO
	this->id = dataNode.id;
	this->data = dataNode.data;
	this->children = dataNode.children;
}

DataNode::DataNode(const Node& node, char data) {
	// TODO
	this->id = node.getId();
	this->data = data;
	/*
	for(int i = 0; i<node.getChildren().size();i++){
		this->children[i] = node.getChildren()[i];
	}
	*/
}

char DataNode::getData() const {
	// TODO
	return this->data;
}

// This is already implemented for you, do NOT change it!
ostream& operator<<(ostream& os, const DataNode& dataNode) {
	os << "[" << "(" << dataNode.id << ", \'" << dataNode.data << "\')";
	for (int i = 0; i < dataNode.children.size(); i++)
		os << ", " << *dataNode.children[i];
	os << "]";
	return os;
}
