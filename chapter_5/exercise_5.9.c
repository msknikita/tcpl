/* Rewrite the routines day_of_year and month_day with pointers instead of indexing. */

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

	printf("%d %d -> %d %d\n", date, year, m, d);
	printf("%d %d -> %d %d\n", month, day, day_of_year(year, month, day), year);

	return 0;
}

int day_of_year(int year, int month, int day)
{
	int leap;
	char *p;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	p = daytab[leap];

	while (--month)
		day += *++p;

	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int leap;
	char *p;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

	p = daytab[leap];

	while (yearday > *p++)
		yearday -= *p;

	*pmonth = p - *(daytab + leap);
	*pday = yearday;
}