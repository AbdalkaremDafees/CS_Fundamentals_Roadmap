/*
        Problem #09: Write a Program to Print Year Calendar
*/
#include <iostream>
using namespace std;

bool IsLeapYear(short year) {
    // if year is divisible by 4 AND not divisible by 100
    // OR if year is divisible by 400
    // then it is a leap year
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

short NumberOfDaysInMonth(short year, short month) {
    short arr[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (month == 2) ? (IsLeapYear(year) ? 29 : 28) : arr[month-1];
}

short DayOrder(short year, short month, short day) {
    short a, y, m;

    a = (14 - month) / 12;
    y = year - a;
    m = month + 12 * a - 2;

    return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m / 12))) % 7;
}

short ReadValue(string message) {
    short value;
    cout << message;
    cin >> value;
    return value;
}

string MonthName(short DayOrder) {
    string monthName[13] = { "", "Jan", "Feb", "Mar", "Apr", "Jul", "Jun",
                             "Aug", "Sep", "Oct", "Nov", "Dec"};
    return monthName[DayOrder];
}

void PrintMonthCalendar(short year, short month) {
    
    // Index of the day from 0 to 6
    short TheDayOrder = DayOrder(year, month, 1);

    short NumOfDay = NumberOfDaysInMonth(year, month);

    // Print the current month name
    printf("\n _______________%s_______________\n\n", MonthName(month).c_str());

    // Print the columns
    printf(" Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    // Print appropriate spaces
    for(int i = 0; i < TheDayOrder; i++) printf("     ");

    int ctr = 0;
    for (int j = 1; j <= NumOfDay; j++) {
        printf("%5d", j);

        if (++ctr == 7) {
            ctr = 0;
            printf("\n");
        }
    }

    printf("\n _________________________________\n");
}

void PrintYearCalendar(short year) {
    printf("\n _________________________________\n\n");
    printf("         Calendar - %d\n", year);
    printf(" _________________________________\n");
    
    for(int i = 1; i <= 12; i++ ) PrintMonthCalendar(year, i);
}

int main() {
    short year = ReadValue("Please Enter a Year? ");
    
    PrintYearCalendar(year);
    
    return 0;
}
