
/**
 *	Name:	Casey Richardson
 *	SID: 	20056054
 *	Date: 	9/17/2013
 *	Prof:	David Egle
 *	Class:	CSCI 3334
 *
 *	File: This file is the main point of the interface.
 */

#include <iostream>
#include <cstdlib>
#include <vector>

#include "cstr.h"
#include "utils.h"

using namespace std;

int main(int argc, char **argv)
{
	string input;
	string clearStr("clear");
	string buildStr("make");
	string exitStr("exit");

	system("clear");

	cout << "<======= + + + + CCLI + + + + =======>" << endl << endl;
	cout << "    Casey's Command Line Interface    " << endl << endl;
	cout << "<======= + + + + ==== + + + + =======>" << endl;
	cout << "   Copyright©  Casey Richardson 2013  " << endl << endl;
	while(true)
	{
		cout << "> ";
		getline(cin, input);

		vector<string> command = cstr::tokenizeCommand(input);
        
        if(command.empty())
            continue;
        
		if(isCommand(command[0]))
		{
			if(cstr::cstrcmp(command[0], exitStr))
			{
				break;
			}
			else if(cstr::cstrcmp(command[0], clearStr))
			{
				system("clear");
			}
			else if(cstr::cstrcmp(command[0], buildStr))
			{
				system(input.c_str());
			}
			else
			{
				if(commandExists(command[0]))
				{
					string builtCommand = "./CCLI/bin/" + command[0] + " " + buildParamString(command);
					system(builtCommand.c_str());
				}
				else
				{
					cout << "Command \'" << command[0] << "\' is not yet implemented!" << endl;
				}
			}
		}
		else
		{
			cout << "Command not recognized!" << endl;
		}
	}

	return 0;
}