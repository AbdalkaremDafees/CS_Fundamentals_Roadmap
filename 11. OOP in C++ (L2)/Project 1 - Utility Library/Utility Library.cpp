#include <iostream>
#include "clsUtility.h"
using namespace std;

int main()
{
    // Random Numbers and Chars + Generate Word and Keys
    clsUtility::Srand();
    cout << clsUtility::RandomNumber(1, 10) << '\n';
    cout << clsUtility::GetRandomCharacter(clsUtility::MixChars) << '\n';
    cout << clsUtility::GenerateWord(clsUtility::MixChars, 8) << '\n';
    cout << clsUtility::GenerateKey(clsUtility::CapitalLetter) << '\n';
    clsUtility::GenerateKeys(clsUtility::CapitalLetter, 10);

    cout << endl;

    // Swap Int 
    int x = 10, y = 20;
    cout << x << " " << y << endl;
    clsUtility::Swap(x, y);
    cout << x << " " << y << endl;

    cout << endl;

    // Swap String 
    string S1 = "ABC", S2 = "XYZ";
    cout << S1 << " " << S2 << endl;
    clsUtility::Swap(S1, S2);
    cout << S1 << " " << S2 << endl;

    cout << endl;

    // Swap Dates 
    clsDate Date1(10, 1, 2022), Date2(5, 7, 2026);
    cout << Date1.DateToString() << " " << Date2.DateToString() << endl;
    clsUtility::Swap(Date1, Date2);
    cout << Date1.DateToString() << " " << Date2.DateToString() << endl;

    cout << endl;



    return 0;
}
