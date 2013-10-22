
/**
 *	Name:	Casey Richardson
 *	SID: 	20056054
 *	Date: 	9/17/2013
 *	Prof:	David Egle
 *	Class:	CSCI 3334
 */

////////////////////////////////////////////////////////////////////
// This file acts as the sole processor of assembly files.        //
// It contains the logic for all parts of the two-pass assembler. //
////////////////////////////////////////////////////////////////////
 
#include "assembler.h"

/**
 * Opcode that takes a number of args and the hex code associated with the mnemonic.
 */
struct opcode
{
	int numArgs;
	int hexCode;

	opcode(){}
	opcode(int nArgs, int hCode)
	{
		numArgs = nArgs;
		hexCode = hCode;
	}
};

/**
 * Puts all our opcodes into the opcode map.
 */
void assembler::buildOpcodeMap()
{
	opcodes["add"]      = opcode(1 ,0x18);
	opcodes["and"]      = opcode(1 ,0x58);
	opcodes["comp"]     = opcode(1 ,0x28);
	opcodes["div"]      = opcode(1 ,0x24);
	opcodes["j"]        = opcode(1 ,0x3C);
	opcodes["jeq"]      = opcode(1 ,0x30);
	opcodes["jgt"]      = opcode(1 ,0x34);
	opcodes["jlt"]      = opcode(1 ,0x38);
	opcodes["jsub"]     = opcode(1 ,0x48);
	opcodes["lda"]      = opcode(1 ,0x00);
	opcodes["ldch"]     = opcode(1 ,0x50);
	opcodes["ldl"]      = opcode(1 ,0x08);
	opcodes["ldx"]      = opcode(1 ,0x04);
	opcodes["mul"]      = opcode(1 ,0x20);
	opcodes["or"]       = opcode(1 ,0x44);
	opcodes["rd"]       = opcode(1 ,0xD8);
	opcodes["rsub"]     = opcode(0 ,0x4C);
	opcodes["sta"]      = opcode(1 ,0x0C);
	opcodes["stch"]     = opcode(1 ,0x54);
	opcodes["stl"]      = opcode(1 ,0x14);
	opcodes["stx"]      = opcode(1 ,0x10);
	opcodes["sub"]      = opcode(1 ,0x1C);
	opcodes["td"]       = opcode(1 ,0xE0);
	opcodes["tix"]      = opcode(1 ,0x2C);
	opcodes["wd"]       = opcode(1 ,0xDC);
}

/**
 * Puts all the default and custom errors into the error map.
 */
void assembler::buildErrorMap()
{
	errors["duplicateLabel"]    = 0x100000;
	errors["illegalLabel"]      = 0x100001;
	errors["illegalOperation"]  = 0x100002;
	errors["illegalOperand"]    = 0x100003;
	errors["illegalStart"]      = 0x100004;
	errors["illegalEnd"]        = 0x100005;
	errors["tooManySymbols"]    = 0x100006;
	errors["programTooLong"]    = 0x100007;
	errors["redefinedStart"]   	= 0x100008;
}

/**
 * Validates that all the fields in the passed in command are correct.
 * @param command - A vector containing a tokenized command.
 */
void assembler::validateTokenizedCommand(vector<string> &command)
{
	int size = command.size();
	string opcode = command[(size < 3 ? 0 : 1)];

	switch(command.size())
	{
		case 2:
		{
			if(checkOpcodeMapForKey(opcode))
			{
				if(opcodes[opcode].numArgs == 1) { return; }
				else { command.pop_back(); }
			}
			break;
		}
		case 3:
		{
			if(checkOpcodeMapForKey(opcode)) { return; }
			break;
		}
	}
}

/**
 * Returns the potential number of items in the passed in line.
 * @param  line - The line that we are checking.
 * @return The potential number of items in the line.
 */
int assembler::getNumberOfItems(string &line) 
{
	return isalpha(line[0]) ? 3 : 2; 
}

/**
 * Returns true if the opcode map contains the given key.
 * @param  key - The key we will look for in the opcode map.
 * @return A bool representing whether or not the key is in the map.
 */
bool assembler::checkOpcodeMapForKey(string &key) 
{
	map<string, opcode>::const_iterator itr;

	itr = opcodes.find(key);

	return itr != opcodes.end();
}

/**
 * Returns true if the symbols map contains the given key.
 * @param  key - The key we will look for in the symbols map.
 * @return A bool representing whether or not the key is in the map.
 */
bool assembler::checkSymbolMapForKey(string &key)
{
	map<string, int>::const_iterator itr;

	itr = symbols.find(key);

	return itr != symbols.end();
}

/**
 * Pass one of the two-pass assembler.
 */
void assembler::passOne()
{
	string line;
	string intermediateLine;
	string listingLine;
	vector<string> tokeLine;
	int locctr = -99;

	ofstream listingFile((parsingFilename + ".listing").c_str());
	ofstream objectFile((parsingFilename + ".object").c_str());
	ofstream intermediateFile((parsingFilename + ".output").c_str());

	while(getline(*(parsingFile), line))
	{
		if(line[0] != '.')
		{
			tokeLine = astr::tokenizeStatement(line, getNumberOfItems(line));

			if(tokeLine.size() > 0)
			{
				validateTokenizedCommand(tokeLine);

				intermediateLine = createIntermediateLine(locctr, tokeLine, line);
				cout << intermediateLine;
				intermediateFile << intermediateLine;
			}
		}
	}

	cout << "Pass one completed!" << endl;
}

/**
 * Pass two of the two-pass assembler.
 */
void assembler::passTwo()
{
	cout << "Pass two is not yet implemented!" << endl;
}

/**
 * Creates and returns the 
 * @param  loc - A reference to the locctr.
 * @param  line - A vector of the tokenized and validated source statement.
 * @param  origLine - The original line before being tokenized and validated.
 * @return A string containing all the information necessary for the intermediate file.
 */
string assembler::createIntermediateLine(int &loc, vector<string> &line, string &origLine)
{
	ostringstream stream;
	ostringstream warnings;

	int update = 0;
	int size = line.size();
	string opcode = line[(size < 3 ? 0 : 1)];

	if(!cstr::cstrcmp(opcode, start)) {
		switch(size)
		{
			case 1: case 2:
			{
				update = 3;
				break;
			}
			case 3:
			{
				if(loc == -99) {
					warnings << errors["illegalStart"] << " "; 
				}

				if(!checkSymbolMapForKey(line[0])) {
					symbols[line[0]] = loc; 

					if(!isalpha(line[0][0])) {
						warnings << errors["illegalLabel"] << " ";
					}
				} else {
					warnings << errors["dupLabel"] << " "; 
				}

				if(checkOpcodeMapForKey(opcode)) {
					update = 3; 
				} else {
					if(cstr::cstrcmp(opcode, word)) {
						update = 3;
					} else if(cstr::cstrcmp(opcode, resb)) {
						int num = cstr::convertStringToInt(line[2]);

						if(num != INT_MIN) {
							update = num;
						} else {
							warnings << errors["illegalOperand"] << " ";
						}
					} else if(cstr::cstrcmp(opcode, resw)) {
						int num = cstr::convertStringToIntWithBase(line[2], 10);

						if(num != INT_MIN) {
							update = 3 * num; 
						} else { 
							warnings << errors["illegalOperand"] << " "; 
						}
					} else if(cstr::cstrcmp(opcode, byte)) {
						int num = astr::numberBytesFromLiteral(line[2]);

						if(num != INT_MIN) {
							char type = line[2][0];
 
							update = num;

							if(type == 'x'){
								if((num + 1) % 2 != 0 || num >= 32) {
									cout << endl << num << endl;
									warnings << errors["illegalOperand"] << " ";
								}
							} else if(type == 'c') {
								if(num > 30) {
									warnings << errors["illegalOperand"] << " ";
								}
							}
						} else {
							update = 3;
							warnings << errors["illegalOperand"] << " ";
						}
					} else {
						update = 3;
						warnings << errors["illegalOperation"] << " ";
					}
				}


				break;
			}
		}
	} else {
		if(loc != -99) {
			warnings << errors["redefinedStart"] << " "; 
		}

		loc = cstr::convertStringToIntWithBase(line[2], 16);
		if(loc == INT_MIN) {
			warnings << errors["illegalOperand"] << " "; 
		}

		symbols[line[0]] = loc;
	}
	
	stream << setw(18) << astr::buildString(line) << "\t" << setw(4) << hex << loc << "\t" << warnings.str() << endl;
	
	cout << warnings.str();

	loc += update;
	
	return stream.str();
}

/**
 * A parameterized constructor that takes a filename to the file we will assemble.
 */
assembler::assembler(string filename)
{
	buildOpcodeMap();
	buildErrorMap();

	parsingFilename = filename;
	parsingFile = new ifstream(filename.c_str());

	if(!*(parsingFile))
	{
		cerr << "The file \"" << filename << "\" could not be opened. Please ensure that it exists and is in the current directory." << endl;
	}
	else
	{
		start 	= "start";
		end 	= "end";
		word 	= "word";
		resb 	= "resb";
		resw 	= "resw";
		byte 	= "byte";

		passOne();
		passTwo();
	}
}

/**
 * Destructor for our assembler.
 */
assembler::~assembler()
{
	parsingFile->close();
	delete parsingFile;
}