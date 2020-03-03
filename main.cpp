/**************************************************************************
* Comp 15 Spring 2019 
* Filename: main.cpp
* Contains: Main implementation
* Part of: Project 2 assignment "Grep" for Comp 15 Fall 2018
* Author: Lewis Bobrow
*************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "Gerp.h"

using namespace std;

int main(int argc, char* argv[]){
	//checks if there is an invalid number of commandline arguments
	if((argc < 3) || (argc > 5)){
		cerr << "usage: ./the_gerp directory " << endl;
		return 0;
	}
	//creates a tree of directories from the first argument
	//sets the root of this tree equal to a DirNode.
	FSTree directories = FSTree(argv[1]);
	DirNode *root = directories.getRoot();
	Gerp gerp;

	//sets the outfile to be the second argument
	//indexes all the words in the root directory
	gerp.set_outfile(argv[2]);

	gerp.index_directory(root, "");

	if(argc == 3){
		//gets the user's command
		gerp.get_command();
	} else{
		gerp.read_command(argv[4]);
	}
	
	return 0;
}