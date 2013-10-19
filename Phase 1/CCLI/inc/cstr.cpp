
/**
 *	Name:	Casey Richardson
 *	SID: 	20056054
 *	Date: 	9/17/2013
 *	Prof:	David Egle
 *	Class:	CSCI 3334
 *
 *	File: This file serves as an all-purpose reusable string utility class. The name "cstr" stands for "Casey String."
 */

#include <iostream>
#include <vector>

#include "cstr.h"

using namespace std;

/**
 *	String function that breaks the string according to its whitespace.
 */
vector<string> cstr::tokenizeCommand(string &input)
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

				output.push_back(csubstr(input, beginWord, endWord));
			}
		}
	}

	return output;
}

/**
 *	String function that returns a substring of the input string.
 */
string cstr::csubstr(string &input, int begin, int end)
{
	if(end <= input.length())
	{
		char sub[end - begin];

		for(int j = begin, k = 0; j <= end; j++, k++)
		{
			if(j != end)
				sub[k] = input[j];
			else
				sub[k] = '\0';
		}

		string s(sub);
		return s;
	}
	else
	{
		string s;
		return s;
	}
}

bool cstr::cstrcmp(string &input1, string &input2)
{
	if(input1.length() != input2.length())
	{
		return false;
	}
	else
	{
		for (int i = 0; i < input1.length(); i++)
		{
			if(input1[i] != input2[i])
				return false;
		}

		return true;
	}
}

bool cstr::cstrcmpchar(char *input1, char *input2)
{
	if(cstrlen(input1) != cstrlen(input2))
	{
		return false;
	}
	else
	{
		for (int i = 0; i < cstrlen(input1); i++)
		{
			if(input1[i] != input2[i])
				return false;
		}

		return true;
	}
}

int cstr::cstrlen(char *input)
{
	int i = 0;

	while(input[i] != '\0')
	{
		i++;
	}

	return i;
}

string cstr::upper(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

string cstr::lower(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}