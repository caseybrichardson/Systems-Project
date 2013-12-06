
/**
 *	Name:	Casey Richardson
 *	SID: 	20056054
 *	Date: 	9/17/2013
 *	Prof:	David Egle
 *	Class:	CSCI 3334
 */

//////////////////////////////////////////////////////////////////
// This file serves to be a specialized string library serving  //
// the purpose of assisting with assembler string functions     //
//////////////////////////////////////////////////////////////////

#ifndef A_STR
#define A_STR

#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <climits>
#include <cctype>

#include "cstr.h"

using namespace std;

class astr{
public:
	static vector<string> tokenizeStatement(string &input, int numItems);
	static string buildString(const vector<string> &params);
	static int numberCharsFromLiteral(string &input);
	static string stringFromLiteral(string &input);
};

#endif