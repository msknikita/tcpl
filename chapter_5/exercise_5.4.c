/* Write the function strend(s,t), which returns 1 if the string t occurs at the end of the string s,
 * and zero otherwise.
 */

#include <stdio.h>

#define MAXLINE 20

int strend(char *, char *);

int main()
{
	char s[MAXLINE] = "foobar";
	char t[MAXLINE] = "bar";

	printf("%d\n", strend(s, t));

	return 0;
}

int strend(char *s, char *t)
{
	char *bs = s;
	char *bt = t;

	for (; *s; ++s);
	for (; *t; ++t);

	for (; *s == *t; --s, --t)
		if (t == bt || s == bs)
			break;

	if (*s == *t && t == bt && *s != '\0')
		return 1;
	else
		return 0;
}