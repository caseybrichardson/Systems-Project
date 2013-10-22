
/**
 *	Name:	Casey Richardson
 *	SID: 	20056054
 *	Date: 	9/17/2013
 *	Prof:	David Egle
 *	Class:	CSCI 3334
 */

//////////////////////////////////////////////////////////////////
// This file acts as the entry point for the help program.      //
//////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>

#include "cstr.h"

using namespace std;

string commands[] = {
	"load 		<filename> 			- loads the specified file",
	"execute 					- executes the loaded file",
	"debug 						- allows use of the debugger",
	"dump 		<start> <end>			- dumps the loaded program",
	"help 		[opt]<command>			- gives information on commands",
	"assemble 	<filename> 			- assembles program into file",
	"directory 					- lists the files in current directory",
	"exit 						- exits the CCLI"
};

void display();
void display(int i);

int main(int argc, char **argv)
{
	string commands[] = {"load", "execute", "debug", "dump", "help", "assemble", "directory", "exit"};

	if(argc == 1)
	{
		display();
	}
	else
	{
		string currArg(argv[1]);

		for(int i = 0; i < 8; i++)
		{
			if(cstr::cstrcmp(currArg, commands[i]))
				display(i);
		}
	}

	return 0;
}

void display()
{
	for(int i = 0; i < 8; i++)
	{
		display(i);
	}
}

void display(int i)
{
	cout << commands[i] << endl;
}