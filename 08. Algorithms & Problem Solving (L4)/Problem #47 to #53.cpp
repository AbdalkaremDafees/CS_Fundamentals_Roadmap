/*
 * Problem #47 to #53: Write a Program to Optimized Date Operations 
 * ====================================================
 * @inspiration: Dr.Mohammed educational implementation
 * @improvement: Replaced iterative approach with direct calculations
 * @performance: From O(n) to O(1) complexity
 *
 * Original approach (professor):
 *   - Used while loops to increment dates day by day
 *   - Great for understanding the logic
 *   - Heavy for production use
 *
 * My optimized approach:
 *   - Direct mathematical calculations
 *   - Cleaner and more maintainable
 *   - Production-ready performance
 *
 * Credit to Dr.Abo-Hadhoud for teaching me the fundamentals! 🎓
 * ====================================================
 */

#include <iostream>
#include<ctime>
using namespace std;

struct stDate {
	short Day, Month, Year;
};

short DayOfWeekOrder(short Day, short Month, short Year)
{
	short a, y, m;
	a = (14 - Month) / 12;
	y = Year - a;
	m = Month + (12 * a) - 2;
	// Gregorian:
	//0:sun, 1:Mon, 2:Tue...etc
	return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m)/ 12)) % 7;
}

short DayOfWeekOrder(stDate Date)
{
	return DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
}

string DayShortName(short DayOfWeekOrder)
{
	string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
	return arrDayNames[DayOfWeekOrder];
}

stDate GetSystemDate()
{
	stDate Date;

	time_t now = time(0);
	tm ltm;

	localtime_s(&ltm, &now);

	Date.Day = ltm.tm_mday;
	Date.Month = 1 + ltm.tm_mon;
	Date.Year = 1900 + ltm.tm_year;

	return Date;
}

bool IsEndOfWeek(stDate Date1) {
	return DayOfWeekOrder(Date1) == 6;
}

bool IsWeekEnd(stDate Date1) {
	short DayOrderInWeek = DayOfWeekOrder(Date1);
	return DayOrderInWeek == 5 || DayOrderInWeek == 6;
}

bool IsBusinessDay(stDate Date1) {
	return !IsWeekEnd(Date1);
}

short  DaysUntilTheEndOfWeek(stDate Date1) {
	return 6 - DayOfWeekOrder(Date1);
}

bool IsLeapYear(short Year) {
	return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
}

short NumberOfDaysInThisMonth(short Month, short Year) {
	if (Month < 1 || Month > 12) return 0;
	short MonthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : MonthDays[Month - 1];
}

short DaysUntilTheEndOfMonth(stDate Date1) {
	short MonthDays = NumberOfDaysInThisMonth(Date1.Month, Date1.Year);
	return MonthDays - Date1.Day;
}

short NumberOfDaysFromBeginingOfTheYear(stDate Date1) {
	short SumOfDays = 0;

	for (int i = 0; i < Date1.Month; i++) {
		SumOfDays += NumberOfDaysInThisMonth(i, Date1.Year);
	}

	SumOfDays += Date1.Day;

	return SumOfDays;
}

short DaysUntilTheEndOfYear(stDate Date1) {
	short NumberOfDaysInYear;
	(IsLeapYear(Date1.Year)) ? NumberOfDaysInYear = 366 : NumberOfDaysInYear = 365;

	short NumberOfDaysFromBegingOfYear = NumberOfDaysFromBeginingOfTheYear(Date1);

	return NumberOfDaysInYear - NumberOfDaysFromBegingOfYear;
}

int main()
{
	stDate Date1 = GetSystemDate();
	cout << "\nToday is " << DayShortName(DayOfWeekOrder(Date1)) << " , " 
		 << Date1.Day << "/" << Date1.Month << "/" << Date1.Year << endl;

	//---------------------
	cout << "\nIs it End of Week?\n";
	if (IsEndOfWeek(Date1))
		cout << "Yes it is Saturday, it's of Week.";
	else
		cout << "No it's Not end of week.";
	
	//---------------------
	cout << "\n\nIs it Weekend?\n";
	if (IsWeekEnd(Date1))
		cout << "Yes it is a week end.";
	else
		cout << "No today is " <<
		DayShortName(DayOfWeekOrder(Date1)) << ", Not a weekend.";
	
	//---------------------
	cout << "\n\nIs it Business Day?\n";
	if (IsBusinessDay(Date1))
		cout << "Yes it is a business day.";
	else
		cout << "No it is NOT a business day.";
	
	//---------------------
	cout << "\n\nDays until end of week : " << DaysUntilTheEndOfWeek(Date1) << " Day(s).";
	
	//---------------------
	cout << "\nDays until end of month : " << DaysUntilTheEndOfMonth(Date1) << " Day(s).";
	
	//---------------------
	cout << "\nDays until end of year : " << DaysUntilTheEndOfYear(Date1) << " Day(s).";

	system("pause>0");
	return 0;
}