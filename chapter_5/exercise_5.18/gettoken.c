#include <ctype.h>
#include <string.h>
#include "main.h"

extern char token[];
extern int tokentype;

int gettoken(void)
{
	int c;
	void ungetch(int);
	char *p = token;

	if ((c = getter()) == '(') {
		if ((c = getter()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		else {
			ungetch(c);
			return tokentype = '(';
		}
	}
	else if (c == '[') {
		for (*p++ = c; (*p++ = getter()) != ']'; );
		*p = '\0';
		return tokentype = BRACKETS;
	}
	else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	}
	else
		return tokentype = c;
}

int getter(void)
{
	int c;

	while ((c = getch()) == ' ' || c == '\t');
	return c;
}