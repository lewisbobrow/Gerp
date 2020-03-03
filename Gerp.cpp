/**************************************************************************
* Comp 15 Spring 2019 
* Filename: Gerp.cpp
* Contains: Implementation of the Gerp class
* Part of: Project 2 assignment "Grep" for Comp 15 Fall 2018
* Author: Lewis Bobrow
*************************************************************************/

#include "Gerp.h"

using namespace std;


// Function: Default Constructor
// Parameters: none
// Returns: none
// Does: Initializes the bucket size and creates the vector of WordNodes and
// 		 sets the outfile to an empty string.
Gerp::Gerp()
{
	buckets = 1242000; 
	for(int i = 0; i < buckets; i++){
		WordNode* Empty_Word = new WordNode;
		table.push_back(Empty_Word);
	}
    outfile = "";
    num_elem = 0;
    load_factor = 0;
}


// Function: Default Destructor
// Parameters: none
// Returns: none
// Does: Destructs the hash table by deleting every node in its linked list
//       and then deleting the WordNode itself
Gerp::~Gerp()
{
	for(int i = 0; i < buckets; i++){
		table.at(i)->info_list.clear();
		table.erase(table.begin() + i);
	}
	table.clear();
}


// Function: set_outfile
// Parameters: string
// Returns: none
// Does: sets the outfile location to be something else
void Gerp::set_outfile(string file)
{
	outfile = file;
	return;
}


// Function: insert
// Parameters: WordNode
// Returns: none
// Does: inserts the given WordNode into the hash table, rehashes the
//		 key if there is already something in that position
void Gerp::insert(WordNode *Node)
{
	unsigned int key = hash<string>{}(Node->word) % buckets;
	// if(key < 0){
	// 	key = -key;
	// }
	check:
	if(table.at(key)->word == ""){
		table.at(key)->word = Node->word;
		table.at(key)->info_list = Node->info_list;
	} else{
		key = (key * key + 1) % buckets;
		goto check;
	}
}


// Function: get
// Parameters: string
// Returns: WordNode
// Does: returns the WordNode at a key calculated based on the given string
WordNode* Gerp::get(string s)
{
	unsigned int key = hash<string>{}(s) % buckets;
	check:
	if((table.at(key)->word == "") || (table.at(key)->word == s)){
		return table.at(key);
	} else{
		key = (key * key + 1) % buckets;
		goto check;
	}
}


// Function: index_file
// Parameters: string
// Returns: none
// Does: indexes all the words in the given file by converting them
//       to lower case and inserting them, along with an InfoNode
//       of its line, line number and path into the hash table
void Gerp::index_file(string path)
{
	ifstream inFile;
	inFile.open(path);
	if(!inFile.is_open()){
		throw runtime_error("Could not build index, exiting.");
	}
	string line;
	int counter = 0;
	while(!inFile.eof()){
		getline(inFile, line);
		counter++;
		istringstream iss(line);
		string word;
		while(iss >> word){
			word = strip_string(word);
			int word_len = word.length();
			string lower;
			for(int i = 0; i < word_len; i++){
				lower += tolower(word[i]);
			}
			InfoNode* word_info = new InfoNode;
			word_info->path = path;
			word_info->line = line;
			word_info->lineNum = counter;
			if(get(lower)->word == lower){
				get(lower)->info_list.push_back(word_info);
			} else{
				get(lower)->word = lower;
				get(lower)->info_list.push_back(word_info);
				// num_elem++;
				// load_factor = (num_elem * 100) / (buckets);
				// if(load_factor > 75){
				// 	int new_buckets = buckets + 500000;
				// 	table.reserve(new_buckets);
				// 	for(int i = buckets; i < new_buckets; i++){
				// 		WordNode* Empty_Word = new WordNode;
				// 		table.push_back(Empty_Word);
				// 	}
				// 	buckets = new_buckets;
				// }
			}
		}	
	}
}


// Function: index_directory
// Parameters: DirNode
// Returns: none
// Does: goes through the directory, and recursively indexes every file 
//       into the hash table in both itself and every other subdirectory within
//       the directory
void Gerp::index_directory(DirNode *Node, string path)
{
	path = path + Node->getName() + "/";
	for(int i = 0; i < Node->numSubDirs(); i++){
		DirNode *current(Node->getSubDir(i));
		index_directory(current, path);
	}
	for(int i = 0; i < Node->numFiles(); i++){
		string file_path = path + Node->getFile(i);
cerr << file_path << endl;
cerr << num_elem << endl;
cerr << buckets << endl;
cerr << load_factor << endl;
		index_file(file_path);
	}
}


// Function: get_command
// Parameters: nothing
// Returns: nothing
// Does: gets the command from the user using cin, and either queries the word
//       in the table, or performs another command specified by the @ symbol.
void Gerp::get_command()
{
	bool quit = false;
	ofstream out;
	out.open(outfile);

	while(!quit){
		cout << "Query?" << endl;
		string command;
		getline(cin, command);
		stringstream ss(command);
		string a, b;
		ss >> a;
		ss >> b;

		if(a == "@i" || a == "@insensitive"){
			istringstream iss(b);
			string command_word;
			while(iss >> command_word){
				int length = command_word.length();
				string lower;
				for(int i = 0; i < length; i++){
					lower += tolower(command_word[i]);
				}
				int vector_size = get(lower)->info_list.size();
				if(vector_size == 0){
					out << "query: not found." << endl;
					continue;
				}
				for(int i = 0; i < vector_size; i++){
						out << get(lower)->info_list.at(i)->path << ":" << 
						get(lower)->info_list.at(i)->lineNum << ": " <<
						get(lower)->info_list.at(i)->line << endl;
				}
			}
			// int length = b.length();
			// string lower;
			// for(int i = 0; i < length; i++){
			// 	lower += tolower(b[i]);
			// }
			// int vector_size = get(lower)->info_list.size();
			// if(vector_size == 0){
			// 	out << "query: not found." << endl;
			// 	continue;
			// }
			// for(int i = 0; i < vector_size; i++){
			// 	out << get(lower)->info_list.at(i)->path << ":" << 
			// 	get(lower)->info_list.at(i)->lineNum << ": " <<
			// 	get(lower)->info_list.at(i)->line << endl;
			// }
		} else if(a == "@q" || a == "quit"){
			quit = true;
			break;
		} else if(a == "@f"){
			outfile = b;
			out.close();
			out.open(outfile);
		} else{
			istringstream iss(command);
			string command_word;
			while(iss >> command_word){
				int length = command_word.length();
				string lower;
				for(int i = 0; i < length; i++){
					lower += tolower(command_word[i]);
				}
				int vector_size = get(lower)->info_list.size();
				if(vector_size == 0){
					out << "query: not found." << endl;
					continue;
				}
				for(int i = 0; i < vector_size; i++){
					string curr_line = get(lower)->info_list.at(i)->line;
					istringstream iss(curr_line);
					string curr_word;
					while(iss >> curr_word){
						if(curr_word == lower){
							out << get(lower)->info_list.at(i)->path << ":" << 
							get(lower)->info_list.at(i)->lineNum << ": " <<
							get(lower)->info_list.at(i)->line << endl;
						}
					}
				}
			}
		}
	}
	cout << "Goodbye! Thank you and have a nice day." << endl;
	return;
}


// Function: read_command
// Parameters: nothing
// Returns: nothing
// Does: same as get_command, but reads from a file
void Gerp::read_command(string inputFile)
{
	bool quit = false;
	ifstream inFile;
	inFile.open(inputFile);
	
	ofstream out;
	out.open(outfile);

	if(inFile.fail()){
		cout << "ERROR: File cannot be opened" << endl;
		return;
	}
	if(!inFile.is_open()){
		cout << "ERROR: File cannot be opened" << endl;
		return;
	}
	while(!inFile.eof()){
		string command;
		getline(inFile, command);
		stringstream ss(command);
		string a, b;
		ss >> a;
		ss >> b;
		b = strip_string(b);

		if(a == "@i" || a == "@insensitive"){
			istringstream iss(b);
			string command_word;
			while(iss >> command_word){
				int length = command_word.length();
				string lower;
				for(int i = 0; i < length; i++){
					lower += tolower(command_word[i]);
				}
				int vector_size = get(lower)->info_list.size();
				if(vector_size == 0){
					out << "query: not found." << endl;
					continue;
				}
				for(int i = 0; i < vector_size; i++){
						out << get(lower)->info_list.at(i)->path << ":" << 
						get(lower)->info_list.at(i)->lineNum << ": " <<
						get(lower)->info_list.at(i)->line << endl;
				}
			}
		} else if(a == "@q" || a == "quit"){
			quit = true;
		} else if(a == "@f"){
			outfile = b;
			out.close();
			out.open(outfile);
		} else{
			istringstream iss(command);
			string command_word;
			while(iss >> command_word){
				int length = command_word.length();
				string lower;
				for(int i = 0; i < length; i++){
					lower += tolower(command_word[i]);
				}
				int vector_size = get(lower)->info_list.size();
				if(vector_size == 0){
					out << "query: not found." << endl;
					continue;
				}
				for(int i = 0; i < vector_size; i++){
					string curr_line = get(lower)->info_list.at(i)->line;
					istringstream iss(curr_line);
					string curr_word;
					while(iss >> curr_word){
						if(curr_word == lower){
							out << get(lower)->info_list.at(i)->path << ":" << 
							get(lower)->info_list.at(i)->lineNum << ": " <<
							get(lower)->info_list.at(i)->line << endl;
						}
					}
				}
			}
		}
	}
	cout << "Goodbye! Thank you and have a nice day." << endl;
	return;
}


// Function: print
// Parameters: nothing
// Returns: nothing
// Does: Strips non-alphanumeric characters from the beginning and end of a string
string Gerp::strip_string(string s)
{
	string s2 = "";
	int length = s.length();
	int head = 0;
	int tail = length;
	for(int i = 0; i < length; i++)
	{
		if(isalnum(s[i])){
			head = i;
			break;
		}
	}
	for(int i = length; i >= head; i--)
	{
		if(isalnum(s[i])){
			tail = i;
			break;
		}
	}
	for(int i = head; i <= tail; i++)
	{
		s2 = s2 + s[i];
	}
	return s2;
}



