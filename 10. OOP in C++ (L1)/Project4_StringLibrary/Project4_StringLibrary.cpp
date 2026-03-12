/*
            Project 4: String Manipulation Library 
       A Dual-Approach Word Counter Using OOP Principles
*/
#include <iostream>
#include "clsString.h"
using namespace std;

int main()
{
    clsString String1;
    clsString String2("Abdalkarem");

    String1.Value = "Mohammed";

    cout << "String1 = " << String1.Value << endl;
    cout << "String2 = " << String2.Value << endl;

    cout << "Number of words: " << String1.CountWords() << endl;

    cout << "Number of words: "
         << String1.CountWords("Fadi ahmed rateb omer") << endl;

    cout << "Number of words: " 
         << clsString::CountWords("Mohammed Saqer Abu-Hadhoud") << endl;

    //----------------

    clsString String3("hi how are you?");

    cout << "String 3 = " << String3.Value << endl;

    cout << "String Length = " << String3.Length() << endl;

    String3.UpperFirstLetterOfEachWord();
    cout << String3.Value << endl;

    //----------------

    String3.LowerFirstLetterOfEachWord();
    cout << String3.Value << endl;

    //----------------

    String3.UpperAllString();
    cout << String3.Value << endl;

    //----------------

    String3.LowerAllString();
    cout << String3.Value << endl;

    //----------------

    cout << "After inverting a : "
        << clsString::InvertLetterCase('a') << endl;

    //----------------

    String3.Value = "AbCdEfg";

    String3.InvertAllLettersCase();
    cout << String3.Value << endl;

    String3.InvertAllLettersCase();
    cout << String3.Value << endl;

    //----------------
    
    system("pause>0");
    return 0;
}