
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
#include "outputGlobals.h"

using namespace std;

enum recordType
{
	headerType,
	textType,
	endType,
	noneType
};

struct opcode;
struct intermediateLine;
class assembler{
private:
	map<string, int> symbols;
	map<string, opcode> opcodes;
	map<string, int> errors;
	string parsingFilename;
	ifstream *parsingFile;

	int startAddress;
	int endAddress;

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

	void cleanUpPassOne();
	void cleanUpPassTwo();

	string createIntermediateError(string key);

	void printSymbols();

	string createIntermediateLine(int &loc, vector<string> &line, string &origLine);
	string createObjectCode(intermediateLine &line);
	string createListingLine(vector<string> &line, string &origLine);

	bool readSymbolFile(string &filename);

public:
	assembler(string filename);
	~assembler();
};