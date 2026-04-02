/*
        Project 5: Date Library, A complete date handling library
            with multiple constructors and utility functions
*/
#include <iostream>
#include "clsDate.h";
using namespace std;

int main()
{
    clsDate Date1;
    cout << "Date 1: ";
    Date1.Print();

    clsDate Date2("31/1/2022");
    cout << "Date 2: ";
    Date2.Print();

    clsDate Date3(20, 12, 2022);
    cout << "Date 3: ";
    Date3.Print();

    clsDate Date4(250, 2022);
    cout << "Date 4: ";
    Date4.Print();

    cout << "Is Date 4 Valid Date? " << clsDate::IsValidDate(Date4) << '\n';

    cout << "Number Of Seconds In Year " << Date2.Year << ": " << 
        Date2.NumberOfSecondsInAYear(Date2.Year) << " sec\n";

    cout << "Day Short Name In Date 2: " << Date2.DayShortName() << '\n';

    cout << "Month Short Name In Date 3: " << Date3.MonthShortName() << '\n';

    system("pause 0");
    return 0;
}