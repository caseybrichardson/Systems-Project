
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

#include <iostream>
#include <iomanip>
#include <cmath>
#include <climits>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "cstr.h"
#include "assemblerStr.h"

using namespace std;

struct opcode;
class assembler{
private:
	map<string, int> symbols;
	map<string, opcode> opcodes;
	map<string, int> errors;
	string parsingFilename;
	ifstream *parsingFile;

	int startAddress;

	string start;
	string end;
	string word;
	string resb;
	string resw;
	string byte;

	opcode createOpcode(int numArgs, int code);
	
	void buildOpcodeMap();
	void buildErrorMap();

	void validateTokenizedCommand(vector<string> &command);

	int getNumberOfItems(string &line);

	bool checkOpcodeMapForKey(string &key);
	bool checkSymbolMapForKey(string &key);

	void passOne();
	void passTwo();

	string createIntermediateError(string key);

	void printSymbols();

	string createIntermediateLine(int &loc, vector<string> &line, string &origLine);

	void addSymbolToMap(string &key, int location);

public:
	assembler(string filename);
	~assembler();
};