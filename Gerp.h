/**************************************************************************
* Comp 15 Spring 2019 
* Filename: Gerp.h
* Contains: Interface of the Gerp class
* Part of: Project 2 assignment "Grep" for Comp 15 Fall 2018
* Author: Lewis Bobrow
*************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <ostream>
#include <sstream>
#include <iterator>
#include "DirNode.h"
#include "FSTree.h"

using namespace std;

#ifndef GERP_H
#define GERP_H

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

struct WordNode
{
     string word;
     vector<InfoNode*> info_list;
     // WordNode(){
     //    word = "";
     //    InfoNode Empty_Info_Node;
     //    info_list->reserve(10000);
     //    for (int i = 0; i < 10000; ++i) {
     //        info_list->push_back(Empty_Info_Node);
     //    }
     // }
};



class Gerp
{
public:
	Gerp();
    ~Gerp();
    void insert(WordNode *Node);
    void index_file(string path);
	void index_directory(DirNode *Node, string path);
	void get_command();
    void read_command(string inputFile);
    string strip_string(string s);
    WordNode* get(string s);
    void set_outfile(string file);

private:
    vector<WordNode*> table;
	int buckets;
	string outfile;
    int num_elem;
    int load_factor;

};


#endif