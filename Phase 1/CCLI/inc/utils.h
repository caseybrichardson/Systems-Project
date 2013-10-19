
/**
 *	Name:	Casey Richardson
 *	SID: 	20056054
 *	Date: 	9/17/2013
 *	Prof:	David Egle
 *	Class:	CSCI 3334
 *
 *	File: This file contains helper functions.
 */

#ifndef C_UTILS
#define C_UTILS

#include <iostream>
#include <fstream>
#include <vector>

#include "cstr.h"

using namespace std;

bool isCommand(string &command)
{
	string commands[] = {"load", "execute", "debug", "dump", "help", "assemble", "directory", "clear", "make", "exit"};

	for(int i = 0; i < 10; i++)
	{
		if(cstr::cstrcmp(command, commands[i]))
		{
			return true;
		}
	}

	return false;
}

bool commandExists(string &command)
{
	ifstream inputFile(("./CCLI/bin/" + command).c_str());
	return inputFile;
}

string buildParamString(const vector<string> &params)
{
	string paramString;

	for(int i = 1; i < params.size(); i++)
	{
		paramString += params[i];
	}

	return paramString;
}

#endif