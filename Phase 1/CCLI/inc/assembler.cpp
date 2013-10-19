
#include "assembler.h"

// Struct that we use to represent different opcodes and their number of arguments and such.
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

void assembler::buildOpcodeMap()
{
	opcodes["add"] = opcode(1 ,0x18);
	opcodes["and"] = opcode(1 ,0x58);
	opcodes["comp"] = opcode(1 ,0x28);
	opcodes["div"] = opcode(1 ,0x24);
	opcodes["end"] = opcode(-99, 0xAFFF);
	opcodes["j"] = opcode(1 ,0x3C);
	opcodes["jeq"] = opcode(1 ,0x30);
	opcodes["jgt"] = opcode(1 ,0x34);
	opcodes["jlt"] = opcode(1 ,0x38);
	opcodes["jsub"] = opcode(1 ,0x48);
	opcodes["lda"] = opcode(1 ,0x00);
	opcodes["ldch"] = opcode(1 ,0x50);
	opcodes["ldl"] = opcode(1 ,0x08);
	opcodes["ldx"] = opcode(1 ,0x04);
	opcodes["mul"] = opcode(1 ,0x20);
	opcodes["or"] = opcode(1 ,0x44);
	opcodes["rd"] = opcode(1 ,0xD8);
	opcodes["rsub"] = opcode(0 ,0x4C);
	opcodes["sta"] = opcode(1 ,0x0C);
	opcodes["start"] = opcode(-99, 0x9FFF);
	opcodes["stch"] = opcode(1 ,0x54);
	opcodes["stl"] = opcode(1 ,0x14);
	opcodes["stx"] = opcode(1 ,0x10);
	opcodes["sub"] = opcode(1 ,0x1C);
	opcodes["td"] = opcode(1 ,0xE0);
	opcodes["tix"] = opcode(1 ,0x2C);
	opcodes["wd"] = opcode(1 ,0xDC);
}

void assembler::buildErrorMap()
{
	errors["duplicate"] = 0x100000;
	errors["illegalLabel"] = 0x100001;
	errors["illegalOp"] = 0x100002;
	errors["imdsd"] = 0x100003;
	errors["imsd"] = 0x100004;
	errors["imed"] = 0x100005;
	errors["tonsSymbols"] =	0x100006;
	errors["progTooLong"] = 0x100007;
	errors["redefinedStart"] = 0x100008;
}

void assembler::validateTokenizedCommand(vector<string> &command)
{
	string opcode = command[0];

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

int assembler::getNumberOfItems(string &line)
{
	int numItems = 3;

	if(!isalpha(line[0]))
	{
		numItems = 2;
	}

	return numItems;
}

bool assembler::checkOpcodeMapForKey(string &key)
{
	return opcodes.find(key) != opcodes.end();
}

bool assembler::checkSymbolMapForKey(string &key)
{
	return symbols.find(key) != symbols.end();
}

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
			validateTokenizedCommand(tokeLine);

			intermediateLine = createIntermediateLine(intermediateFile, locctr, tokeLine, line);

			
		}
	}

	cout << "Pass one completed!" << endl;
}

void assembler::passTwo()
{
	cout << "Pass two is not yet implemented!" << endl;
}

string createIntermediateLine(ofstream &listing, int &loc, vector<string> &line, string &origLine)
{
	ostringstream stream;

	switch(line.size())
	{
		case 1:
		{

			break;
		}
		case 2:
		{
			if(opcodes[line[0]].hexCode == opcodes["start"].hexCode)
			{
				loc = atoi(tokeLine[1].c_str());
				stream << origLine << " # " << loc << " # " << 
				break;
			}
			else
			{

			}
			break;
		}
		case 3:
		{
			if(opcodes[line[1]].hexCode == opcodes["start"].hexCode)
			{
				loc = atoi(tokeLine[2].c_str());
				stream << origLine << " # " << loc << " # " << 
				break;
			}
			else
			{

			}
			break;
		}
	}

	return stream.str();
}

assembler::assembler(string filename)
{
	buildOpcodeMap();
	buildErrorMap();

	parsingFilename = filename;
	parsingFile = new ifstream(filename.c_str());

	if(!*(parsingFile))
	{
		cerr << "The file: " << filename << " could not be opened. Please ensure that it exists and is in the current directory." << endl;
	}
	else
	{
		passOne();
		passTwo();
	}
}

assembler::~assembler()
{
	parsingFile->close();
	delete parsingFile;
}