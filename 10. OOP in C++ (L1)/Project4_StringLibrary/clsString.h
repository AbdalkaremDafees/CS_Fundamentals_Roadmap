#pragma once

#include <iostream>
using namespace std;

class clsString
{

private:
	string _Value;

public:
	clsString()
	{
		_Value = " ";
	}

	clsString(string Value)
	{
		_Value = Value;
	}

	void SetValue(string Value)
	{
		_Value = Value;
	}

	string GetValue()
	{
		return _Value;
	}

	__declspec(property(get = GetValue, put = SetValue)) string Value;

	static short CountWords(string S1)
	{
		string delim = " "; // delimiter
		short Counter = 0;
		short pos = 0;
		string sWord; // define a string variable

		// use find() function to get the position of the delimiters
		while ((pos = S1.find(delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos); // store the word
			if (sWord != "")
			{
				Counter++;
			}

			//erase() until positon and move to next word.
			S1.erase(0, pos + delim.length());
		}

		if (S1 != "")
		{
			Counter++; // it counts the last word of the string.
		}

		return Counter;
	};

	short CountWords()
	{
		return CountWords(_Value);
	}



	static short Length(string S1)
	{
		return S1.length();
	};

	short Length()
	{
		return _Value.length();
	}

	static string UpperFirstLetterOfEachWord(string S1)
	{

		bool isFirstLetter = true;

		for (short i = 0; i < S1.length(); i++)
		{

			if (S1[i] != ' ' && isFirstLetter)
			{
				S1[i] = toupper(S1[i]);

			}

			isFirstLetter = (S1[i] == ' ' ? true : false);

		}

		return S1;
	}

	void UpperFirstLetterOfEachWord()
	{
		// no need to return value , this function will directly update the object value  
		_Value = UpperFirstLetterOfEachWord(_Value);
	}

	static string  LowerFirstLetterOfEachWord(string S1)
	{

		bool isFirstLetter = true;

		for (short i = 0; i < S1.length(); i++)
		{

			if (S1[i] != ' ' && isFirstLetter)
			{
				S1[i] = tolower(S1[i]);

			}

			isFirstLetter = (S1[i] == ' ' ? true : false);

		}

		return S1;
	}

	void  LowerFirstLetterOfEachWord()
	{
		// no need to return value , this function will directly update the object value  
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	static string UpperAllString(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = toupper(S1[i]);
		}

		return S1;
	}

	void UpperAllString()
	{
		_Value = UpperAllString(_Value);
	}

	static string  LowerAllString(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = tolower(S1[i]);
		}
		return S1;
	}

	void  LowerAllString()
	{
		_Value = LowerAllString(_Value);
	}

	static char InvertLetterCase(char char1)
	{
		return isupper(char1) ? tolower(char1) : toupper(char1);
	}

	static string InvertAllLettersCase(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = isupper(S1[i]) ? tolower(S1[i]) : toupper(S1[i]);
		}

		return S1;
	}

	void InvertAllLettersCase()
	{
		_Value = InvertAllLettersCase(_Value);
	}

};