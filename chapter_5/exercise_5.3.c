/* Write a pointer version of the function strcat(s,t) copies the string t to the end of s. */

#include <stdio.h>

#define MAXLINE 20

void strcat(char *, char *);

int main()
{
	char s[MAXLINE] = "foo";
	char t[MAXLINE] = "bar";

	strcat(s, t);
	printf("%s\n%s\n", s, t);

	return 0;
}

void strcat(char *s, char *t)
{
	while (*++s);
	while (*s++ = *t++);
}