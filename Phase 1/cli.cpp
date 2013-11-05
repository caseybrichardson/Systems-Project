
/**
 *	Name:	Casey Richardson
 *	SID: 	20056054
 *	Date: 	9/17/2013
 *	Prof:	David Egle
 *	Class:	CSCI 3334
 */

/////////////////////////////////////////////////////
// This file acts as the main entry point for the  //
// interface and handles all program requests.     //
/////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <vector>

#include <pwd.h>
#include <unistd.h>

#include "cstr.h"
#include "utils.h"

using namespace std;

int main(int argc, char **argv)
{
	string input;
	string lastCommand;
	string clearStr("clear");
	string buildStr("make");
	string lastStr("!!");
	string exitStr("exit");
	char name[1024];
	gethostname(name, 1024);
	string hostname(name);

	struct passwd *passwd;
	passwd = getpwuid(getuid());

	system("clear");

	cout << "<======= + + + + CCLI + + + + =======>" << endl << endl;
	cout << "    Casey's Command Line Interface    " << endl << endl;
	cout << "<======= + + + + ==== + + + + =======>" << endl;
	cout << "   Copyright©  Casey Richardson 2013  " << endl << endl;
	while(true)
	{
		cout << passwd->pw_name << "@" << hostname << "$ ";
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
				lastCommand = clearStr;
				system("clear");
			}
			else if(cstr::cstrcmp(command[0], buildStr))
			{
				lastCommand = input.c_str();
				system(input.c_str());
			}
			else if(cstr::cstrcmp(command[0], lastStr))
			{
				if(lastCommand != "") 
				{
					cout << lastCommand << endl;
					system(lastCommand.c_str());
				} 
				else 
				{
					cout << "No previous working command!" << endl;
				}
			}
			else
			{
				if(commandExists(command[0]))
				{
					string builtCommand = "./CCLI/bin/" + command[0] + " " + buildParamString(command);
					lastCommand = builtCommand;
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