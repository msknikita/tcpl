#include <stdio.h>
#include <ctype.h>
#include "calc.h"

int getop(char s[])
{
	int i = 0, c, t;
	static int last_c = 0;

	if (last_c == 0)
		c = getch();
	else {
		c = last_c;
		last_c = 0;
	}

	while ((s[0] = c) == ' ' || c == '\t')
		c = getch();

	s[1] = '\0';

	if (!isdigit(c) && c != '.')
		return c;

	i = 0;

	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()));

	if (c == '.')
		while (isdigit(s[++i] = c = getch()));

	s[i] = '\0';

	if (c != EOF)
		last_c = c;

	return NUMBER;
}
