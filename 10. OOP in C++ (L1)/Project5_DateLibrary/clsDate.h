#pragma warning(disable : 4996)
#pragma once

#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <ctime>
using namespace std;

class clsDate
{

private:
    short _Day = 1, _Month = 1, _Year = 1900;

public:
    // Default Constructor: Initializes date with current system date
    clsDate()
    {
        time_t t = time(nullptr);
        tm* now = localtime(&t);

        // Extract day, month, year
        _Day = now->tm_mday;           // Day of month (1-31)
        _Month = now->tm_mon + 1;      // Month (1-12) - tm_mon is 0-11
        _Year = now->tm_year + 1900;   // Year (e.g., 2026) - tm_year is years since 1900
    }

    static clsDate GetSystemDate()
    {
        //system date
        time_t t = time(0);
        tm* now = localtime(&t);
        short Day, Month, Year;

        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;

        return clsDate(Day, Month, Year);
    }

    // Parameterized Constructor: Initializes date from string in format "dd/mm/yyyy"
    clsDate(string sDate)
    {
        vector<string> vDate;
        vDate = clsString::Split(sDate, "/");

        _Day = stoi(vDate[0]);
        _Month = stoi(vDate[1]);
        _Year = stoi(vDate[2]);
    }

    // Parameterized Constructor: Initializes date with specific day, month, and year values
    clsDate(short Day, short Month, short Year)
    {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }

    clsDate(short DayOrderInYear, short Year)
    {
        clsDate Date1 = GetDateFromDayOrderInYear(DayOrderInYear, Year);

        _Day = Date1.Day;
        _Month = Date1.Month;
        _Year = Date1.Year;
    }

    // Setter for Day property
    void SetDay(short Day)
    {
        _Day = Day;
    }

    // Getter for Day property
    short GetDay()
    {
        return _Day;
    }
    __declspec(property(get = GetDay, put = SetDay)) short Day;

    // Setter for Month property
    void SetMonth(short Month)
    {
        _Month = Month;
    }

    // Getter for Month property
    short GetMonth()
    {
        return _Month;
    }
    __declspec(property(get = GetMonth, put = SetMonth)) short Month;

    // Setter for Year property
    void SetYear(short Year)
    {
        _Year = Year;
    }

    // Getter for Year property
    short GetYear()
    {
        return _Year;
    }
    __declspec(property(get = GetYear, put = SetYear)) short Year;

    // Prints the date in string format
    void Print()
    {
        cout << DateToString() << endl;
    }

    // Static method: Converts a given clsDate object to string format "dd/mm/yyyy"
    static string DateToString(clsDate Date)
    {
        return to_string(Date.Day) + "/" +
            to_string(Date.Month) + "/" + to_string(Date.Year);
    }

    // Instance method: Converts current date object to string format "dd/mm/yyyy"
    string DateToString()
    {
        return DateToString(*this);
    }

    // Static method: Validates if a given date is valid
    // Checks day range (1-31), month range (1-12), February special cases for leap years,
    // and ensures day does not exceed days in the specified month
    static bool IsValidDate(clsDate Date)
    {

        if (Date.Day < 1 || Date.Day>31)
            return false;

        if (Date.Month < 1 || Date.Month>12)
            return false;

        if (Date.Month == 2)
        {
            if (isLeapYear(Date.Year))
            {
                if (Date.Day > 29)
                    return false;
            }
            else
            {
                if (Date.Day > 28)
                    return false;
            }
        }

        short DaysInMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

        if (Date.Day > DaysInMonth)
            return false;

        return true;

    }

    // Instance method: Validates the current date object
    bool IsValid()
    {
        return IsValidDate(*this);
    }

    static bool isLeapYear(short Year)
    {
        // if year is divisible by 4 AND not divisible by 100
        // OR if year is divisible by 400
        // then it is a leap year
        return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
    }

    bool isLeapYear()
    {
        return isLeapYear(_Year);
    }

    static short NumberOfDaysInAMonth(short Month, short Year)
    {
        if (Month < 1 || Month>12)
            return 0;
        int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) :
            days[Month - 1];
    }

    static clsDate GetDateFromDayOrderInYear(short
        DateOrderInYear, short Year)
    {
        clsDate Date;

        short RemainingDays = DateOrderInYear;
        short MonthDays = 0;

        Date.Year = Year;
        Date.Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(Date.Month, Year);

            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                Date.Month++;
            }
            else
            {
                Date.Day = RemainingDays;
                break;
            }
        }

        return Date;
    }
};