
/**
 *	Name:	Casey Richardson
 *	SID: 	20056054
 *	Date: 	9/17/2013
 *	Prof:	David Egle
 *	Class:	CSCI 3334
 */


//////////////////////////////////////////////////////////////////
// This file serves to be a specialized string library serving  //
// the purpose of assisting with assembler string functions     //
//////////////////////////////////////////////////////////////////

#include "assemblerStr.h"

/**
 * Tokenizes a source line from an assembly file.
 * @param  input - The source line.
 * @param  numItems - The number of expected items in the passed in line.
 * @return A vector containing the tokens from the string.
 */
vector<string> astr::tokenizeStatement(string &input, int numItems)
{
    // Stores the broken string and is returned at the end.
	vector<string> output;
	int numWords;

    // Index trackers of the beginning and end of words.
	int beginWord;
	int endWord;
	bool inWord = false;
	bool inQuotes = false;
	bool hasBeenInQuotes = false;

	for(int i = 0; i <= input.length(); i++)
	{
		char currChar = input[i];

		if(output.size() >= numItems)
		{
			break;
		}

		if(currChar == '\'' || currChar == '\"')
		{
			hasBeenInQuotes = true;
			inQuotes = !inQuotes;
		}

        // Make sure that we're not currently inside a word.
		if(!inWord)
		{
            // If the character is not a whitespace character then we start making a new word.
			if(isalnum(currChar))
			{
				beginWord = i;
				inWord = true;
			}
		}
		else
		{
            // Checks if the current character is some form of whitespace.
			if((isspace(currChar) || iscntrl(currChar)) && !inQuotes)
			{
				endWord = i;
				inWord = false;

				if(hasBeenInQuotes)
				{
					string lit = cstr::csubstr(input, beginWord, endWord);
					lit[0] = tolower(lit[0]);
					output.push_back(lit);
				}
				else
				{
					output.push_back(cstr::lower(cstr::csubstr(input, beginWord, endWord)));
				}
				
				hasBeenInQuotes = false;
			}
		}
	}

	return output;
}

/**
 * Concantenates and returns a vector of strings.
 * @param  params - A vector of strings that are from a tokenized string.
 * @return A concantenated string made up of the values from the passed in vector.
 */
string astr::buildString(const vector<string> &params)
{
	string paramString;

	for(int i = 0; i < params.size(); i++)
	{
		paramString += params[i] + " ";
	}

	return paramString;
}

/**
 * Takes an input that contains a literal value and returns the number of bytes contained in it.
 * @param  input - The literal value.
 * @return The number of bytes in the literal.
 */
int astr::numberCharsFromLiteral(string &input)
{
	int num_bytes = 0;

	if(input[1] == '\'' && input[input.length() - 1] == '\'' && (input[0] == 'c' || input[0] == 'x'))
	{
		for(int i = 2; isalnum(input[i]) || isspace(input[i]); i++)
		{
			num_bytes++;
		}

		return num_bytes;
	}
	else
	{
		return INT_MIN;
	}
}

string astr::stringFromLiteral(string &input)
{
	string literal;

	if(input[1] == '\'' && input[input.length() - 1] == '\'' && (input[0] == 'c' || input[0] == 'x'))
	{
		for(int i = 2; isalnum(input[i]) || isspace(input[i]); i++)
		{
			literal += input[i];
		}

		return literal;
	}
	else
	{
		return "";
	}
}
