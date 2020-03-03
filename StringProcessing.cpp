/**************************************************************************
* Comp 15 Spring 2019 
* Filename: StringProcessing.cpp
* Contains: Implementation of string processing
* Part of: Project 2 assignment "Gerp" for Comp 15 Spring 2019
* Author: Lewis Bobrow
**************************************************************************/

#include <iostream>
#include <string>

using namespace std;

// Function: print
// Parameters: nothing
// Returns: nothing
// Does: Strips non-alphanumeric characters from the beginning and end of a string
void stripString(){
	string s;
	while(cin >> s){
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

		cout << s2 << endl;
	}
}

int main()
{
	stripString();
	return 0;
}

