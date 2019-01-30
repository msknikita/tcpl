/* As written, getint treats a + or - not followed by a digit as a valid representation of zero.
 * Fix it to push such a character back on the input.
 */

#include <ctype.h>
#include <stdio.h>

#define BUFSIZE 1000

char buf[BUFSIZE];
int bufp = 0;

int getint(int *);
int getch(void);
void ungetch(int c);

int main()
{
	int n, type, array[BUFSIZE];

	for (n = 0; n < BUFSIZE && (type = getint(&array[n])) != EOF; ++n)
		printf("array[%d] = %d %s\n", n, type ? array[n] : type, type ? "" : "is not a number");

	return 0;
}

int getint(int *pn)
{
	int c, sign;

	while (isspace(c = getch()));

	if (!isdigit(c) && c != EOF && c != '+' && c != '-')
		return 0;

	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		c = getch();
		if (!isdigit(c)) {
			ungetch(sign == 1 ? '+' : '-');
			return 0;
		}
	}

	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
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