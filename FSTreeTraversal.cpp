/**************************************************************************
* Comp 15 Spring 2019 
* Filename: FSTreeTraversal.cpp
* Contains: Implementation of file system traversal
* Part of: Project 2 assignment "Gerp" for Comp 15 Spring 2019
* Author: Lewis Bobrow
**************************************************************************/

#include <iostream>
#include <FSTree.h>
#include <DirNode.h>

using namespace std;

// Function: print
// Parameters: string, DirNode
// Returns: nothing
// Does: prints all the files within the given directory by recursing through
//       the current directory's subdirectories, and printing the current
//       directory's files.
void print(string directory, DirNode *curr){
	int subdirs = curr->numSubDirs();
	for(int i = 0; i < subdirs; i++){
		DirNode *subdir = curr->getSubDir(i);
		string subdirname = subdir->getName();
		string newroot = directory + "/" + subdirname;
		print(newroot, subdir);
	}
	
	int files = curr->numFiles();
	for(int i = 0; i < files; i++){
		string filename = curr->getFile(i);
		cout << directory << "/" << filename << endl;
	}
	
	cout << directory << endl;
}

int main(int argc, char *argv[])
{
    if(argc != 2){
    	cerr << "usage: ./the_gerp directory " << endl;
    	return 0;
    }

    string root = argv[1];
    FSTree files(root);
    print(root, files.getRoot());

    return 0;
}

