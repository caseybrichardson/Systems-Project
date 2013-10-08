
/**
 *	Name:	Casey Richardson
 *	SID: 	20056054
 *	Date: 	9/17/2013
 *	Prof:	David Egle
 *	Class:	CSCI 3334
 *
 *	File: This file serves as an all-purpose reusable string utility class. The name "cstr" stands for "Casey String."
 */

#ifndef C_STR
#define C_STR

#include <iostream>
#include <vector>

using namespace std;

class cstr{
public:
	static vector<string> tokenizeCommand(string &input);
	static string csubstr(string &input, int begin, int end);
	static bool cstrcmp(string &input1, string &input2);
	static bool cstrcmpchar(char *input1, char *input2);
	static int cstrlen(char *input);
};

#endif