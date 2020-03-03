/**************************************************************************
* Comp 15 Spring 2019 
* Filename: gerptest.cpp
* Contains: Unit testing file
* Part of: Project 2 assignment "Grep" for Comp 15 Fall 2018
* Author: Lewis Bobrow
*************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "Gerp.h"
#include "DirNode.h"
#include "FSTree.h"

using namespace std;

int main(){
	//creating instance of Gerp
	Gerp gerptest;

	//creating an InfoNode to insert into WordNode linked list
	InfoNode *New_Word_Info0 = new InfoNode;
	New_Word_Info0->path = "path to a";
	New_Word_Info0->line = "this is the a line";
	New_Word_Info0->lineNum = 1;

	//creating a Word Node to insert into Gerp's hash table
	WordNode *New_Node0 = new WordNode;
	New_Node0->word = "a";

	//creating an InfoNode to insert into WordNode linked list
	InfoNode *New_Word_Info1 = new InfoNode;
	New_Word_Info1->path = "path to asdf";
	New_Word_Info1->line = "this is the asdf line";
	New_Word_Info1->lineNum = 1;

	//creating a Word Node to insert into Gerp's hash table
	WordNode *New_Node1 = new WordNode;
	New_Node1->word = "asdf";


	//creating an InfoNode to insert into WordNode linked list
	InfoNode *New_Word_Info2 = new InfoNode;
	New_Word_Info2->path = "path to blank";
	New_Word_Info2->line = "this is the blank line";
	New_Word_Info2->lineNum = -1;

	//creating a Word Node to insert into Gerp's hash table
	WordNode *New_Node2 = new WordNode;
	New_Node2->word = " ";


	//creating an InfoNode to insert into WordNode linked list
	InfoNode *New_Word_Info3 = new InfoNode;
	New_Word_Info3->path = "path to asdf 2";
	New_Word_Info3->line = "this is the second asdf line";
	New_Word_Info3->lineNum = 2;

	//inserting the InfoNodes into the WordNodes
	New_Node1->info_list.push_back(New_Word_Info1);
	New_Node2->info_list.push_back(New_Word_Info2);
	New_Node1->info_list.push_back(New_Word_Info3);
	New_Node0->info_list.push_back(New_Word_Info0);

	
	//TESTING INSERT

	//BASE CASE
	gerptest.insert(New_Node0);
	cerr << "inserting a" << endl;

	//EDGE CASE, inserting a Node with 2 items in the linked list of InfoNodes
	gerptest.insert(New_Node1);
	cerr << "inserting asdf" << endl;

	//EDGE CASE, inserting a blank
	gerptest.insert(New_Node2);
	cerr << "inserting ' ', shouldn't create a key" << endl;


	//QUERYING BASE CASE (NO CAPS)
	cerr << "Querying for a: " << endl;
	cerr << gerptest.get("a")->word << endl;
	int a_size = gerptest.get("a")->info_list.size();
	for(int i = 0; i < a_size; i++){
		cerr << gerptest.get("a")->info_list.at(i)->path << 
		":" << gerptest.get("a")->info_list.at(i)->lineNum << ": " <<
		gerptest.get("a")->info_list.at(i)->line << endl;
	}

	//EDGE CASE QUERYING CAPS
	cerr << "Querying for a: " << endl;
	cerr << gerptest.get("asdf")->word << endl;
	int asdf_size = gerptest.get("asdf")->info_list.size();
	for(int i = 0; i < asdf_size; i++){
		cerr << gerptest.get("asdf")->info_list.at(i)->path << 
		":" << gerptest.get("asdf")->info_list.at(i)->lineNum << ": " <<
		gerptest.get("asdf")->info_list.at(i)->line << endl;
	}


	//QUERYING EDGE CASE CAPS
	cerr << "Querying for A (SHOULD BE EMPTY): " << endl;
	cerr << gerptest.get("A")->word << endl;
	int A_size_2 = gerptest.get("A")->info_list.size();
	for(int i = 0; i < A_size_2; i++){
		cerr << gerptest.get("A")->info_list.at(i)->path << 
		":" << gerptest.get("A")->info_list.at(i)->lineNum << ": " <<
		gerptest.get("A")->info_list.at(i)->line << endl;
	}

	//EDGE CASE QUERYING CAPS
	cerr << "Querying for ASDF (SHOULD BE EMPTY): " << endl;
	cerr << gerptest.get("ASDF")->word << endl;
	int ASDF_size_2 = gerptest.get("ASDF")->info_list.size();
	for(int i = 0; i < ASDF_size_2; i++){
		cerr << gerptest.get("ASDF")->info_list.at(i)->path << 
		":" << gerptest.get("ASDF")->info_list.at(i)->lineNum << ": " <<
		gerptest.get("ASDF")->info_list.at(i)->line << endl;
	}


	//TESTING STRIP_STRING

	//BASE CASE
	string s1 = "^^^^^^ll;kj/.,,.`/1`=fjalkj1/^^^^^";
	cerr << "original: " << s1 << endl;
	s1 = gerptest.strip_string(s1);
	cerr << "result: " << s1 << endl;

	//EDGE CASE, NO AL NUM
	string s2 = "$^^^^^$$$$^^^^^$";
	cerr << "original: " << s2 << endl;
	s2 = gerptest.strip_string(s2);
	cerr << "result: " << s2 << endl;

	// //TESTING INDEX FILE / DIRECTORY

	// //SETTING OUTFILE
	// gerptest.set_outfile("outfile2.txt");

	// //CREATING DIRNODE OF ROOT FOR DIRECTORY
	// FSTree directories = FSTree("./gerp /comp/15/files/lab12/");
	// DirNode *root1 = directories.getRoot();


	// //BASE CASE
	// gerptest.index_directory(root1, "");

	return 0;
}