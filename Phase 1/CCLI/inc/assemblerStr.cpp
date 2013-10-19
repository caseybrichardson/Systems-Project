
#include "assemblerStr.h"

/**
 *	String function that breaks the string according to its whitespace.
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

	for(int i = 0; i <= input.length(); i++)
	{
		char currChar = input[i];

		if(output.size() >= numItems)
		{
			break;
		}

        // Make sure that we're not currently inside a word.
		if(!inWord)
		{
            // If the character is not a whitespace character then we start making a new word.
			if(currChar != ' ' && currChar != '\t')
			{
				beginWord = i;
				inWord = true;
			}
		}
		else
		{
            // Checks if the current character is some form of whitespace.
			if(currChar == ' ' || currChar == '\t' || currChar == '\0')
			{
				endWord = i;
				inWord = false;

				output.push_back(cstr::lower(cstr::csubstr(input, beginWord, endWord))) ;
			}
		}
	}

	return output;
}

string astr::buildString(const vector<string> &params)
{
	string paramString;

	for(int i = 0; i < params.size(); i++)
	{
		paramString += params[i] + " ";
	}

	return paramString;
}