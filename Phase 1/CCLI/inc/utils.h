
/**
 *	Name:	Casey Richardson
 *	SID: 	20056054
 *	Date: 	9/17/2013
 *	Prof:	David Egle
 *	Class:	CSCI 3334
 */

////////////////////////////////////////////////////////////
// This file contains helper functions for the interface. //
////////////////////////////////////////////////////////////

#ifndef C_UTILS
#define C_UTILS

#include <iostream>
#include <fstream>
#include <vector>

#include "cstr.h"

using namespace std;

/**
 * Checks if the passed in command is registered within the program.
 * @param  command - The command trying to be accessed.
 * @return A bool representing whether or not that command is available.
 */
bool isCommand(string &command)
{
	string commands[] = {"load", "execute", "debug", "dump", "help", "assemble", "directory", "clear", "make", "!!", "exit"};

	for(int i = 0; i < 11; i++)
	{
		if(cstr::cstrcmp(command, commands[i]))
		{
			return true;
		}
	}

	return false;
}

/**
 * Checks if the registered command is available within the local bin folder.
 * @param  command - The command trying to be accessed.
 * @return A bool representing whether or not that command is available.
 */
bool commandExists(string &command)
{
	ifstream inputFile(("./CCLI/bin/" + command).c_str());
	return inputFile;
}

/** TODO: Remove this definition and move it to the general purpose cstr class.
 * Concantenates and returns a vector of strings.
 * @param  params - A vector of strings that are from a tokenized string.
 * @return A concantenated string made up of the values from the passed in vector.
 */
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