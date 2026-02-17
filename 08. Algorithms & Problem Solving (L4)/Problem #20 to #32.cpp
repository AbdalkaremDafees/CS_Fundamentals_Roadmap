/*
			Problem #20 to #32: Write a program to increase day, month, and year
							by X days, X month, and X years.
*/
#include <iostream>
using namespace std;

struct stDate {
	short Day, Year, Month;
};

short ReadValue(string Message) {
	short Value;
	cout << Message;
	cin >> Value;
	return Value;
}

stDate ReadFullDate() {
	stDate Date;
	Date.Day = ReadValue("Please Enter Day? ");
	Date.Month = ReadValue("Please Enter Month? ");
	Date.Year = ReadValue("Please Enter Year? ");
	cout << '\n';
	return Date;
}

short IsLeapYear(short Year) {
	return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
}

short NumberOfDaysInMonth(short Month, short Year) {
	if (Month < 1 || Month > 12) return 0;
	short MonthDays[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 ,31 };
	return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : MonthDays[Month - 1];
}

bool IsLastDayInMonth(stDate Date1) {
	return (Date1.Day == NumberOfDaysInMonth(Date1.Month, Date1.Year) );
}

bool IsLastMonthInYear(short Month) {
	return Month == 12;
}

stDate IncreaseDateByOneDay(stDate Date1) {
	if (IsLastDayInMonth(Date1)) {
		if (IsLastMonthInYear(Date1.Month)) {
			Date1.Day = 1;
			Date1.Month = 1;
			Date1.Year++;
		}
		else {
			Date1.Day = 1;
			Date1.Month++;
		}
	}
	else {
		Date1.Day++;
	}
	return Date1;
}

stDate IncreaseDateByXDays(short XDays, stDate Date1) {
	for (int i = 1; i <= XDays; i++) {
		Date1 = IncreaseDateByOneDay(Date1);
	}
	return Date1;
}

stDate IncreaseDateByOneWeek(stDate Date1) {
	for (int i = 1; i <= 7; i++) {
		Date1 = IncreaseDateByOneDay(Date1);
	}
	return Date1;
}

stDate IncreaseDateByXWeeks(short XWeeks, stDate Date1) { 
	for (int i = 1; i <= XWeeks; i++) {
		Date1 = IncreaseDateByOneWeek(Date1);
	}
	return Date1;
}

stDate IncreaseDateByOneMonth(stDate Date1) {
	if (IsLastMonthInYear(Date1.Month)) {
		Date1.Month = 1;
		Date1.Year++;
	}
	else {
		Date1.Month++;
	}

	short NumberOfDaysInOneMonth = NumberOfDaysInMonth(Date1.Month, Date1.Year);
	if (Date1.Day > NumberOfDaysInOneMonth) {
		Date1.Day = NumberOfDaysInOneMonth;
	}
	return Date1;
}

stDate IncreaseDateByXMonths(short XMonths, stDate Date1) {
	for (int i = 1; i <= XMonths; i++) {
		Date1 = IncreaseDateByOneMonth(Date1);
	}
	return Date1;
}

stDate IncreaseDateByOneYear(stDate Date) {
	Date.Year++;
	return Date;
}

stDate IncreaseDateByXYears(short Years, stDate Date) {
	for (short i = 1; i <= Years; i++)
	{
		Date = IncreaseDateByOneYear(Date);
	}
	return Date;
}

stDate IncreaseDateByXYearsFaster(short Years, stDate Date) {
	Date.Year += Years;
	return Date;
}

stDate IncreaseDateByOneDecade(stDate Date) {
	//Period of 10 years
	Date.Year += 10;
	return Date;
}

stDate IncreaseDateByXDecades(short Decade, stDate Date) {
	for (short i = 1; i <= Decade * 10; i++)
	{
		Date = IncreaseDateByOneYear(Date);
	}
	return Date;
}

stDate IncreaseDateByXDecadesFaster(short Decade, stDate Date) {
	Date.Year += Decade * 10;
	return Date;
}

stDate IncreaseDateByOneCentury(stDate Date) {
	//Period of 100 years
	Date.Year += 100;
	return Date;
}

stDate IncreaseDateByOneMillennium(stDate Date) {
	//Period of 1000 years
	Date.Year += 1000;
	return Date;
}

int main() {
	stDate Date1 = ReadFullDate();

	cout << "\nDate After: \n";

	Date1 = IncreaseDateByOneDay(Date1);
	cout << "\n01-Adding one day is: "
		<< Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

	Date1 = IncreaseDateByXDays(10, Date1);
	cout << "\n02-Adding 10 days is: "
		<< Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

	Date1 = IncreaseDateByOneWeek(Date1);
	cout << "\n03-Adding one week is: "
		<< Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

	Date1 = IncreaseDateByXWeeks(10, Date1);
	cout << "\n04-Adding 10 weeks is: "
		<< Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

	Date1 = IncreaseDateByOneMonth(Date1);
	cout << "\n05-Adding one month is: "
		<< Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

	Date1 = IncreaseDateByXMonths(5, Date1);
	cout << "\n06-Adding 5 months is: "
		<< Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

	Date1 = IncreaseDateByOneYear(Date1);
	cout << "\n07-Adding one year is: "
		<< Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

	Date1 = IncreaseDateByXYears(10, Date1);
	cout << "\n08-Adding 10 Years is: "
		<< Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

	Date1 = IncreaseDateByXYearsFaster(10, Date1);
	cout << "\n09-Adding 10 Years (faster) is: "
		<< Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

	Date1 = IncreaseDateByOneDecade(Date1);
	cout << "\n10-Adding one Decade is: "
		<< Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

	Date1 = IncreaseDateByXDecades(10, Date1);
	cout << "\n11-Adding 10 Decades is: "
		<< Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

	Date1 = IncreaseDateByXDecadesFaster(10, Date1);
	cout << "\n12-Adding 10 Decade (faster) is: "
		<< Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

	Date1 = IncreaseDateByOneCentury(Date1);
	cout << "\n13-Adding One Century is: "
		<< Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

	Date1 = IncreaseDateByOneMillennium(Date1);
	cout << "\n14-Adding One Millennium is: "
		<< Date1.Day << "/" << Date1.Month << "/" << Date1.Year;

	system("pause>0");
	return 0;
}
