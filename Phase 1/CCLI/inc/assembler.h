
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

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

	opcode createOpcode(int numArgs, int code);
	
	void buildOpcodeMap();
	void buildErrorMap();

	void validateTokenizedCommand(vector<string> &command);

	int getNumberOfItems(string &line);

	bool checkOpcodeMapForKey(string &key);
	bool checkSymbolMapForKey(string &key);

	void passOne();
	void passTwo();

	string createIntermediateLine(ofstream &listing, int &loc, vector<string> &line, string &origLine);

	void addSymbolToMap(string &key, int location);

public:
	assembler(string filename);
	~assembler();
};