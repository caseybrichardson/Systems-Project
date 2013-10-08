
/**
 *	Name:	Casey Richardson
 *	SID: 	20056054
 *	Date: 	9/17/2013
 *	Prof:	David Egle
 *	Class:	CSCI 3334
 *
 *	File: This file contains the logic for the help program.
 */

#include <iostream>
#include <cstdlib>

#include "cstr.h"

using namespace std;

string commands[] = {
	"load 		<filename> 			- loads the specified file",
	"execute 					- executes the previously loaded file",
	"debug 						- allows use of the debugger",
	"dump 		<start> <end>			- dumps the loaded program",
	"help 						- gives information on available commands",
	"assemble 	<filename> 			- assembles program and saves to file",
	"directory 					- lists the files in the current directory",
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
		string arg(argv[1]);

		for(int i = 0; i < 8; i++)
		{
			if(cstr::cstrcmp(arg, commands[i]))
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