
/**
 *	Name:	Casey Richardson
 *	SID: 	20056054
 *	Date: 	9/17/2013
 *	Prof:	David Egle
 *	Class:	CSCI 3334
 */

//////////////////////////////////////////////////////////////////
// This file acts as the entry point for the assemble program.  //
// It handles no logic of the actual file processing.           //
//////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>

#include "assembler.h"

using namespace std;

int main(int argc, char **argv)
{
	if(argc == 1)
	{
		cout << "Missing filename!" << endl;
	}
	else if(argc >= 2)
	{
		string filename(argv[1]);
		assembler asmblr(filename);
	}

	return 0;
}