/*
            Problem #12: Write a program to read a date, and read how many days
                   to add to it, then print the new date on the screen.
*/
#include <iostream>
using namespace std;


// Know if the year is leap year.
bool isLeapYear(short Year) {
    return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
}

// How many days in a month ?
short NumberOfDaysInMonth(short Month, short Year) {
    if (Month < 1 && Month > 12) return 0;
    short NumOfDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : NumOfDays[Month];
}

// How many days from the begining of the year until user date.
short NumOfDayFromBeginOfYear(short Day, short Month, short Year) {
    short sum = 0;
    for (int i = 1; i < Month; i++) {
        sum += NumberOfDaysInMonth(i, Year);
    }
    sum += Day;
    return sum;
}

// struct for date parts.
struct stDate {
    short Year;
    short Month;
    short Day;
};

// Get the date from the days order in the user year.
stDate getDateFromDayOrderInYear(short DaysOrderInYear, short Year) {
    stDate Date;
    short RemainDays = DaysOrderInYear;
    short MonthDays = 0;

    Date.Year = Year;
    Date.Month = 1;
    
    while (true) {
        MonthDays = NumberOfDaysInMonth(Date.Month, Year);
        if (RemainDays > MonthDays) {
            RemainDays -= MonthDays;
            Date.Month++;
            if (Date.Month > 12) {
                Date.Month = 1;
                Date.Year++;
            }
            
        }
        else {
            Date.Day = RemainDays;
            break;
        }
    }
    return Date;
}

// Add the days orderd in year to days that user want.
short addPrevDayToNewDay(short DaysOrderInYear, short DaysToAdd) {
    return DaysOrderInYear + DaysToAdd;
}

// Read value.
short readValue(string message) {
    short Value;
    cout << message;
    cin >> Value;
    return Value;
}

int main()
{
    // Read Year, Month, and Day.
    short Year = readValue("Please Enter Year? ");
    short Month = readValue("\nPlease Enter Month? ");
    short Day = readValue("\nPlease Enter Day? ");

    // Number Of Days From The Begining Of The Year. 
    short DaysOrderInYear = NumOfDayFromBeginOfYear(Day, Month, Year);

    // How Many Days To Add ?
    short DaysToAdd = readValue("\nHow Many Days To Add? ");

    // Add Previoud Day To The New Number Days.
    short DateAfterAdding = addPrevDayToNewDay(DaysOrderInYear, DaysToAdd);

    // Print Result.
    stDate Date;
    Date = getDateFromDayOrderInYear(DateAfterAdding, Year);
    cout << "Date for [" << DaysToAdd << "] is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;


    return 0;
}
