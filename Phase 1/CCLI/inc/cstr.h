
/**
 *	Name:	Casey Richardson
 *	SID: 	20056054
 *	Date: 	9/17/2013
 *	Prof:	David Egle
 *	Class:	CSCI 3334
 */

//////////////////////////////////////////////////////////////////
// This file serves to be a general purpose replacement string  //
// library (I don't claim this to be in any fashion better)     //
//////////////////////////////////////////////////////////////////

#ifndef C_STR
#define C_STR

#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>

using namespace std;

class cstr{
public:
	static vector<string> tokenizeCommand(string &input);
	static string csubstr(string &input, int begin, int end);
	static bool cstrcmp(string &input1, string &input2);
	static bool cstrcmpchar(char *input1, char *input2);
	static int cstrlen(char *input);
	static string upper(string str);
	static string lower(string str);
	static int convertStringToInt(string &input);
	static int convertStringToIntWithBase(string &input, int b);
};

#endif