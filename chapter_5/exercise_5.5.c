/* Write versions of the library functions strncpy, strncat, and strncmp, 
 * which operate on at most the first n characters of their argument strings.
 * For example, strncpy(s,t,n) copies at most n characters of t to s.
 */

#include <stdio.h>

#define MAXLINE 20

void strncpy(char *, char *, int);
int strncmp(char *, char *, int);
void strncat(char *, char *, int);

int main()
{
	char s[MAXLINE] = "foo";
	char t[MAXLINE] = "bar";

	//strncpy(s, t, 2);
	//strncat(s, t, 3);

	printf("%d\n", strncmp(s, t, 3));

	return 0;
}

void strncpy(char *s, char *t, int n)
{
	int i = 0;

	while (i++ < n && (*s++ = *t++));
}

int strncmp(char *s, char *t, int n)
{
	for (; *s == *t; ++s, ++t)
		if (*s == '\0' || --n <= 0)
			return 0;

	return *s - *t;
}

void strncat(char *s, char *t, int n)
{
	int i = 0;

	while (*++s);
	while (i++ < n && (*s++ = *t++));
}