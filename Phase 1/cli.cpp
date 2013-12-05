
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
#include "outputGlobals.h"

using namespace std;

int main(int argc, char **argv)
{
	string input;
	string clearStr("clear");
	string buildStr("make");
	string changeStr("cd");
	string exitStr("exit");
	char name[1024];
	char cwd[1024];
	gethostname(name, 1024);
	string hostname(name);

	struct passwd *passwd;
	passwd = getpwuid(getuid());

	system("clear");

	cout << WHITE << "<======= + + + + CCLI + + + + =======>" << endl << endl;
	cout << WHITE << "    Casey's Command Line Interface    " << endl << endl;
	cout << WHITE << "<======= + + + + ==== + + + + =======>" << endl;
	cout << WHITE << "   Copyright©  Casey Richardson 2013  " << RESET << endl << endl;
	while(true)
	{
		getcwd(cwd, sizeof(cwd));
		string wd(cwd);
		cout << "[" << passwd->pw_name << "@" <<  hostname << " " << CYAN << wd << RESET << "]$ " << RESET;
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
			/* TODO: Implement directory changing
			else if(cstr::cstrcmp(command[0], changeStr))
			{
				string test = cstr::stringFromStringsWithRange(command, 1, command.size()).c_str();
				cout << test << endl;
				chdir(test.c_str());
			}
			*/
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