/* Write function getfloat, the floating-point analog of getint. */

#include <ctype.h>
#include <stdio.h>

#define BUFSIZE 1000

char buf[BUFSIZE];
int bufp = 0;

int getfloat(float *);
int getch(void);
void ungetch(int c);

int main()
{
	int n, type;
	float array[BUFSIZE];

	for (n = 0; n < BUFSIZE && (type = getfloat(&array[n])) != EOF; ++n)
		printf("array[%d] = %f %s\n", n, type ? array[n] : type, type ? "" : "is not a number");

	return 0;
}

int getfloat(float *pn)
{
	int c, sign;
	float power;

	while (isspace(c = getch()));

	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
		ungetch(c);
		return 0;
	}	

	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-')
		c = getch();

	for (*pn = 0.0; isdigit(c); c = getch())
		*pn = 10.0 * *pn + (c - '0');

	if (c == '.')
		c = getch();

	for (power = 1.0; isdigit(c); c = getch()) {
		*pn = 10.0 * *pn + (c - '0');
		power *= 10.0;
	}

	*pn *= sign / power;

	if (c != EOF)
		ungetch(c);

	return c;
}

int getch(void)
{
	return(bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("many symbols\n");
	else
		buf[bufp++] = c;
}