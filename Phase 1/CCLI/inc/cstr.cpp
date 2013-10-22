
/**
 *	Name:	Casey Richardson
 *	SID: 	20056054
 *	Date: 	9/17/2013
 *	Prof:	David Egle
 *	Class:	CSCI 3334
 */

//////////////////////////////////////////////////////////////////
// This file serves to be a general purpose replacement string  //
// library (I don't claim this to be in any fashion better)     //
//////////////////////////////////////////////////////////////////

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

/**
 * String function that returns a substring of the input string.
 * @param  input - The source string.
 * @param  begin - The index for the beginning of the substring.
 * @param  end - The index for the end of the substring.
 * @return The substring as defined by the begin and end parameters within the input parameter.
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

/**
 * Casey String Comparison, checks if two strings are equal to one another by comparing their length and char sequence.
 * @param  input1 - The first string to compare.
 * @param  input2 - The second string to compare.
 * @return A bool representing whether or not the the strings are equal.
 */
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

/**
 * Casey String Comparison for Character Strings, checks if two character arrays are equal by comparing their length and char sequence.
 * @param  input1 - The first char array to compare.
 * @param  input2 - The second char array to compare.
 * @return A bool representing whether or not the char arrays are equal.
 */
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

/**
 * Takes a string and capitalizes all alphabetic characters within it.
 * @param  str - The string to transform.
 * @return The capitalized string.
 */
string cstr::upper(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

/**
 * Takes a string and makes all alphabetic characters within it lower case.
 * @param  str - The string to transform.
 * @return The lower case string.
 */
string cstr::lower(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

/**
 * Takes a string and extracts the number inside it.
 * @param  input - The string that contains the number.
 * @return The number in the string.
 */
int cstr::convertStringToInt(string &input)
{
	return convertStringToIntWithBase(input, 0);
}

/**
 * Takes a string that has a number of a certain base and extracts it.
 * @param  input - The string that contains the number.
 * @param  b - The base we are looking for.
 * @return The number in the string.
 */
int cstr::convertStringToIntWithBase(string &input, int b)
{
	char *end;

	int num = strtol(input.c_str(), &end, b);

	if(!*end) { return num; }
	else { return INT_MIN; }
}