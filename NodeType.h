/**************************************************************************
* Comp 15 Spring 2019 
* Filename: LinkedList.h
* Contains: Interface of the NodeType
* Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Spring 2019
* Author: Lewis Bobrow
*************************************************************************/

#include <string>

using namespace std;

#ifndef NODE_TYPE_H_
#define NODE_TYPE_H_

//Template Node for the linked list class
template<class E>
struct NodeType
{
	E info;
    NodeType *next;
};

//InfoNode to be used int the linked list of WordNode
struct InfoNode
{
    string path;
    string line;
    int lineNum;
	bool operator==(InfoNode const & rhs) const {
		return this->line == rhs.line;
	}
	ostream & operator << (ostream &out) const {
		out << this->line;
		return out;
	}
};


#endif