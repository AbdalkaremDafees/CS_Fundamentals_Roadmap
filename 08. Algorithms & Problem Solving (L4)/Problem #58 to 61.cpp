/*
		Probem #61: Write a program to count how many days
					overlap between two periods.
*/
#include <iostream>
using namespace std;

struct stDate {
	short Day, Month, Year;
};

struct stPeriod
{
	stDate StartDate;
	stDate EndDate;
};

// Reads a day from the user and returns it
short ReadDay()
{
	short Day;
	cout << "\nPlease enter a Day? ";
	cin >> Day;
	return Day;
}

// Reads a month from the user and returns it
short ReadMonth()
{
	short Month;
	cout << "Please enter a Month? ";
	cin >> Month;
	return Month;
}

// Reads a year from the user and returns it
short ReadYear()
{
	short Year;
	cout << "Please enter a Year? ";
	cin >> Year;
	return Year;
}

// Reads a complete date (day, month, year) from the user and returns it as a stDate structure
stDate ReadFullDate()
{
	stDate Date;
	Date.Day = ReadDay();
	Date.Month = ReadMonth();
	Date.Year = ReadYear();
	return Date;
}

// Reads a period (start date and end date) from the user and returns it as a stPeriod structure
stPeriod ReadPeriod()
{
	stPeriod Period;
	cout << "\nEnter Start Date:\n";
	Period.StartDate = ReadFullDate();
	cout << "\nEnter End Date:\n";
	Period.EndDate = ReadFullDate();
	return Period;
}

// Checks if a year is a leap year and returns true if it is, false otherwise
bool isLeapYear(short Year)
{
	return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

// Returns the number of days in a given month of a specific year
short NumberOfDaysInAMonth(short Month, short Year)
{
	if (Month < 1 || Month>12) return 0;
	int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : days[Month - 1];
}

// Checks if a given date is the last day of its month and returns true if it is, false otherwise
bool IsLastDayInMonth(stDate Date)
{
	return (Date.Day == NumberOfDaysInAMonth(Date.Month, Date.Year));
}

// Checks if a given month is the last month of the year and returns true if it is, false otherwise
bool IsLastMonthInYear(short Month)
{
	return (Month == 12);
}

// Increases a given date by one day and returns the new date
stDate IncreaseDateByOneDay(stDate Date)
{
	if (IsLastDayInMonth(Date))
	{
		if (IsLastMonthInYear(Date.Month))
		{
			Date.Month = 1;
			Date.Day = 1;
			Date.Year++;
		}
		else
		{
			Date.Day = 1;
			Date.Month++;
		}
	}
	else
	{
		Date.Day++;
	}
	return Date;
}

enum enCompare { Before = -1, Equal = 0, After = 1 };

// Compares two dates and returns true if the first date comes before the second date, false otherwise
bool IsDate1BeforeDate2(stDate Date1, stDate Date2) {
	return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
}

// Compares two dates and returns true if they are equal, false otherwise
bool IsDate1EqualDate2(stDate Date1, stDate Date2) {
	return (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false;
}

// Compares two dates and returns true if the first date comes after the second date, false otherwise
bool IsDate1AfterDate2(stDate Date1, stDate Date2) {
	return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
}

// Compares two dates and returns an enCompare value indicating whether Date1 is Before, Equal, or After Date2
enCompare CompareDates(stDate Date1, stDate Date2) {
	if (IsDate1BeforeDate2(Date1, Date2)) return enCompare::Before;
	else if (IsDate1EqualDate2(Date1, Date2)) return enCompare::Equal;
	else return enCompare::After;
}

// Checks if two periods overlap and returns true if they do, false otherwise
bool IsOverlapPeriods(stPeriod Period1, stPeriod Period2) {
	return !(CompareDates(Period2.EndDate, Period1.StartDate) == enCompare::Before ||
			 CompareDates(Period2.StartDate, Period1.EndDate) == enCompare::After);
}

// Checks if a specific date falls within a given period and returns true if it does, false otherwise
bool isDateInPeriod(stDate Date, stPeriod Period)
{
	return !(CompareDates(Date, Period.StartDate) == enCompare::Before ||
			 CompareDates(Date, Period.EndDate) == enCompare::After);
}

// Calculates and returns the difference in days between two dates, with an option to include the end day
int GetDifferenceInDays(stDate Date1, stDate Date2, bool IncludeEndDay = false) {
	int Days = 0;
	while (IsDate1BeforeDate2(Date1, Date2))
	{
		Days++;
		Date1 = IncreaseDateByOneDay(Date1);
	}
	return IncludeEndDay ? ++Days : Days;
}

// Calculates and returns the length of a period in days, with an option to include the end date
int PeriodLengthInDays(stPeriod Period, bool IncludeEndDate = false) {
	return GetDifferenceInDays(Period.StartDate, Period.EndDate, IncludeEndDate);
}

// Counts and returns the number of days that overlap between two periods
int CountOverlapDays(stPeriod Period1, stPeriod Period2) {
	int Period1Length = PeriodLengthInDays(Period1, true);
	int Period2Length = PeriodLengthInDays(Period2, true);
	int CountDays = 0;

	if (!IsOverlapPeriods(Period1, Period2)) return 0;

	if (Period1Length < Period2Length) {
		while (IsDate1BeforeDate2(Period1.StartDate, Period1.EndDate)) {
			if (isDateInPeriod(Period1.StartDate, Period2))
				CountDays++;

			Period1.StartDate = IncreaseDateByOneDay(Period1.StartDate);
		}
	}
	else {
		while (IsDate1BeforeDate2(Period2.StartDate, Period2.EndDate)) {
			if (isDateInPeriod(Period2.StartDate, Period1))
				CountDays++;

			Period2.StartDate = IncreaseDateByOneDay(Period2.StartDate);
		}
	}
	return CountDays;
}

int main()
{
	cout << "\nEnter Period 1 :";
	stPeriod Period1 = ReadPeriod();
	cout << "\nEnter Period 2 :";
	stPeriod Period2 = ReadPeriod();
	cout << "\nOverlap Days Count Is: " << CountOverlapDays(Period1, Period2);
	system("pause>0");
	return 0;
}