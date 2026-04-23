#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "clsDate.h"	
using namespace std;

class clsUtility
{

public:
	static void Srand()
	{
		srand(unsigned(time(NULL)));
	}

	static int RandomNumber(int From, int To)
	{
		int TheRandoumNumber = rand() % (To - From + 1) + From;
		return TheRandoumNumber;
	}

	enum enCharacters {SmallLetter = 1, CapitalLetter = 2, Digits = 3, SpecialChars = 4, MixChars = 5};

	static char GetRandomCharacter(enCharacters enChars)
	{
		switch (enChars)
		{
			case enCharacters::SmallLetter:
				return (char)RandomNumber(97, 122);
			case enCharacters::CapitalLetter:
				return (char)RandomNumber(65, 90);
			case enCharacters::Digits:
				return (char)RandomNumber(48, 57);
			case enCharacters::SpecialChars:
				return (char)RandomNumber(33, 47);
			default:
				return (char)RandomNumber(33, 126);
		}
	}

	static string GenerateWord(enCharacters enChars, short WordLong)
	{
		string S1 = "";
		for (int i = 0; i < WordLong; i++)
		{
			S1 += GetRandomCharacter(enChars);
		}

		return S1;
	}

	static string GenerateKey(enCharacters enChars, short WordLong = 16)
	{
		string S2 = "";
		for (int i = 1; i <= WordLong; i++)
		{
			S2 += GetRandomCharacter(enChars);

			if (i % 4 == 0 && i != WordLong) S2 += "-";
		}

		return S2;
	}

	static void GenerateKeys(enCharacters enChars, short NumberOfKeys, short WordLong = 16)
	{
		string S3 = "";
		for (int j = 1; j <= NumberOfKeys; j++)
		{
			S3 = "";
			for (int i = 1; i <= WordLong; i++)
			{
				S3 += GetRandomCharacter(enChars);

				if (i % 4 == 0 && i != WordLong) S3 += "-";

			}
			cout << "Key [" << j << "] :" << S3 << '\n';
		}
	}

	static  void Swap(int& A, int& B)
	{
		int Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static  void Swap(double& A, double& B)
	{
		double Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static  void Swap(bool& A, bool& B)
	{
		bool Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static  void Swap(char& A, char& B)
	{
		char Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static  void Swap(string& A, string& B)
	{
		string Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static  void Swap(clsDate& A, clsDate& B)
	{
		clsDate::SwapDates(A, B);

	}

};

