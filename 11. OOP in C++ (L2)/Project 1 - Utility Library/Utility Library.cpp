#include <iostream>
#include "clsUtility.h"
using namespace std;

int main()
{
    clsUtility::Srand();
    cout << clsUtility::RandomNumber(1, 10) << '\n';
    cout << clsUtility::GetRandomCharacter(clsUtility::MixChars) << '\n';
    cout << clsUtility::GenerateWord(clsUtility::MixChars, 8) << '\n';
    cout << clsUtility::GenerateKey(clsUtility::CapitalLetter) << '\n';
    clsUtility::GenerateKeys(clsUtility::CapitalLetter, 10);

    cout << endl;

    return 0;
}
