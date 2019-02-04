/* Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing.
 * Good possibilities include getline, atoi, itoa, and their variants, reverse, and strindex and getop.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int getline(char *, int);
int strindex(char *, char *);
void reverse(char *);
int atoi(char *);
void itoa(int, char *);
int getop(char *);

int main()
{

	return 0;
}

int getline(char *s, int lim)
{
	int c;
	char *t = s;

	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;

	if (c == '\n')
		*s++ = c;
	*s = '\0';

	return s - t;
}

int strindex(char *s, char *t)
{
	char *b = s;
	char *p, *r;

	for (; *s != '\0'; ++s) {
		for (p = s, r = t; *r != '\0' && *p == *r; ++p, ++r);

		if (r > t && *r == '\0')
			return s - b;
	}

	return -1;
}

void reverse(char *s)
{
	char *p;
	int c;

	for (p = s + (strlen(s) - 1); s < p; ++s, --p) {
		c = *s;
		*s = *p;
		*p = c;
	}
}

int atoi(char *s)
{
	int n, sign;

	for (; isspace(*s); ++s);

	sign = (*s == '-') ? -1 : 1;

	if (*s == '+' || *s == '-')
		++s;

	for (n = 0; isdigit(*s); ++s)
		n = 10 * n + *s - '0';

	return sign * n;
}

void itoa(int n, char *s)
{
	int sign;
	char *t = s;

	if ((sign = n) < 0)
		n = -n;
	do
		*s++ = n % 10 + '0';
	while ((n /= 10) != 0);

	if (sign < 0)
		*s++ = '-';

	*s = '\0';

	reverse(t);
}

int getop(char *s)
{
	int c;

	while ((*s = c = getch()) == ' ' || c == '\t');

	*(s + 1) = '\0';

	if (!isdigit(c) && c != '.')
		return c;

	if (isdigit(c))
		while (isdigit(*++s = c = getch()));
	if (c == '.')
		while (isdigit(*++s = c = getch()));

	*s = '\0';

	if (c != EOF)
		ungetch(c);

	return NUMBER;
}
