
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
#include <sstream>
#include <cstdlib>
#include <vector>
#include <iomanip>

#include <pwd.h>
#include <unistd.h>

#include "cstr.h"
#include "utils.h"
#include "outputGlobals.h"
#include "sicengine.c"

using namespace std;

int main(int argc, char **argv)
{
	string input;
	string clearStr("clear");
	string buildStr("make");
	string changeStr("cd");
	string catStr("cat");
	string exitStr("exit");

	// Way to make these commands completely break the layout of my project :P
	string execStr("execute");
	string loadStr("load");
	string dumpStr("dump");
	string debugStr("debug");

	ADDRESS progLength;
	ADDRESS endLoc;
	bool fileLoaded;

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
			else if(cstr::cstrcmp(command[0], catStr))
			{
				system(input.c_str());
			}
			else if(cstr::cstrcmp(command[0], execStr))
			{
				if(fileLoaded)
				{
					SICRun(&endLoc, 0);
				}
				else
				{
					cerr << RED << "No file loaded yet." << RESET << endl;
				}
			}
			else if(cstr::cstrcmp(command[0], loadStr))
			{
				if(command.size() == 2)
				{
					SICInit();

					ifstream inputFile(command[1].c_str());

					string inputFileLine;
					string num;

					while(getline(inputFile, inputFileLine))
					{
						if(inputFileLine[0] == 'H')
						{
							string thing = cstr::csubstr(inputFileLine, 13, inputFileLine.length());
							progLength = cstr::convertStringToIntWithBase(thing, 16);
						}
						if(inputFileLine[0] == 'T')
						{
							ADDRESS address;
							BYTE value;
							int holder;

							num = cstr::csubstr(inputFileLine, 1, 7);
							address = cstr::convertStringToIntWithBase(num, 16);

							for(int i = 9; i < inputFileLine.length(); i += 2)
							{

								num = cstr::csubstr(inputFileLine, i, i + 2);
								value = cstr::convertStringToIntWithBase(num, 16);

								PutMem(address, &value, 0);
								address++;
							}
						}
						else if(inputFileLine[0] == 'E')
						{

							num = cstr::csubstr(inputFileLine, 1, inputFileLine.length());
							endLoc = cstr::convertStringToIntWithBase(num, 16);
						}
						else if(inputFileLine[0] != 'H')
						{
							cerr << RED << "There was an error while loading your file." << RESET << endl;
						}
					}

					fileLoaded = true;
				}
				else
				{
					cerr << RED << "Bad Grammar!" << RESET << endl;
				}
			}
			else if(cstr::cstrcmp(command[0], dumpStr))
			{
				if(fileLoaded)
				{
					if(command.size() == 3)
					{
						int startAddress;
						int endAddress;

						BYTE value;
						startAddress = cstr::convertStringToIntWithBase(command[1], 16);
						endAddress = cstr::convertStringToIntWithBase(command[2], 16);

						int count = 0;

						for(int i = startAddress; i < endAddress; i += 2, count++)
						{
							if( count != 0 && count % 16 == 0 )
							{
								cout << endl << hex << i << ": ";
							}

							GetMem(i, &value, 0);
							cout << setfill('0') << setw(2) << (int) value << " ";
						}

						cout << endl;
					}
					else
					{
						cerr << RED << "Bad Grammar!" << RESET << endl;
					}
				}
				else
				{
					cerr << RED << "No file loaded yet." << RESET << endl;
				}
			}
			else if(cstr::cstrcmp(command[0], debugStr))
			{
				/*
				if(fileLoaded)
				{
					ADDRESS lastAddress;
					ADDRESS address = endLoc;
					cout << hex << address << endl;
					bool stepOnce = true;
					bool firstRun = true;
					char command;
					bool breakFlag = false;
					bool shouldStep = true;

					while(!breakFlag && address <= endLoc + progLength && lastAddress != address)
					{
						if(shouldStep)
							SICRun(&address, 1);
						cout << (firstRun ? "Type \'h\' for help.\n" : "");
						firstRun = false;

						if(stepOnce)
						{
							cout << "Command> ";
							cin >> command;

							switch(command)
							{
								case 'h':
									cout << "\'p\' will print all the registers." << endl
										 << "\'c\' will let you continue." << endl
										 << "\'x\' will let you change the value of the index register." << endl
										 << "\'l\' will let you change the value of the linkage register." << endl
										 << "\'a\' will let you change the value of the accumulator." << endl
										 << "\'m\' will let you change the value of any memory location." << endl
										 << "\'s\' will let you stop debugging and continue to the end of the program." << endl
										 << "\'q\' will quit and stop running the program." << endl;
									shouldStep = false;
									break;
								case 'p':
									shouldStep = false;
									break;
								case 'c':
									shouldStep = true;
									continue;
									break;
								case 'x':
									shouldStep = false;
									break;
								case 'l':
									shouldStep = false;
									break;
								case 'a':
									shouldStep = false;
									break;
								case 'm':
									shouldStep = false;
									break;
								case 's':
									stepOnce = false;
									shouldStep = true;
									break;
								case 'q':
									breakFlag = true;
									shouldStep = false;
									break;
								default:
									shouldStep = true;
									break;
							}
						}
					}

					cout << endl;

				}
				else
				{
					cerr << RED << "No file loaded yet." << RESET << endl;
				}*/
				cerr << RED << "H" << BLUE << "E" << YELLOW << "L" << GREEN << "L" << MAGENTA << "O" << RESET << endl;
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