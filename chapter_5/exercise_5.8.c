/* There is no error-checking in day_of_year or month_day. Remedy this defect. */

#include <stdio.h>

int day_of_year(int, int, int);
void month_day(int, int, int *, int *);

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main()
{
	int year = 2016, date = 60, month = 2, day = 29;
	int m, d;

	month_day(year, date, &m, &d);

	printf("%dth day in year %d -> month=%d, day=%d\n", date, year, m, d);
	printf("month=%d, day=%d -> %dth day in year %d\n", month, day, day_of_year(year, month, day), year);

	return 0;
}


int day_of_year(int year, int month, int day)
{
	int i, leap;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	if (month < 1 || month > 12)
		return -1;

	if (day < 1 || day > daytab[leap][month])
		return -1;

	for (i = 1; i < month; ++i)
		day += daytab[leap][i];

	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	if (year < 1) {
		*pmonth = -1;
		*pday = -1;
		return;
	}

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	for (i = 1; i <= 12 && yearday > daytab[leap][i]; ++i)
		yearday -= daytab[leap][i];

	if (i > 12 && yearday > daytab[leap][i]) {
		*pmonth = -1;
		*pday = -1;
	}
	else {
		*pmonth = i;
		*pday = yearday;
	}
}