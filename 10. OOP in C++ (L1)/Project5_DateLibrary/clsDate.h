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
};