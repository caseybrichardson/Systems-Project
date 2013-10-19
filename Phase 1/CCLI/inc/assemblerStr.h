
/**
 *	Name:	Casey Richardson
 *	SID: 	20056054
 *	Date: 	9/17/2013
 *	Prof:	David Egle
 *	Class:	CSCI 3334
 *
 *	File: This file serves as an all-purpose reusable string utility class. The name "cstr" stands for "Casey String."
 */

#ifndef A_STR
#define A_STR

#include <iostream>
#include <string>
#include <vector>

#include "cstr.h"

using namespace std;

class astr{
public:
	static vector<string> tokenizeStatement(string &input, int numItems);
	static string buildString(const vector<string> &params);
};

#endif