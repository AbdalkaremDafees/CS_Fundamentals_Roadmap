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
         << clsString::CountWords("Mohammed Saqer Abu-Hadhoud");
    
    system("pause>0");
    return 0;
}
