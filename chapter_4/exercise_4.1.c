/* Write the function strrindex(s,t) , which returns the position of the rightmost occurrence of t in s , or -1 if there is none. */

#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";

int main()
{
	char line[MAXLINE];
	int found = 0;
	int i, j, pos;

	while (getline(line, MAXLINE) > 0)
		if ((pos = strindex(line, pattern)) >= 0) {
			printf("%d %s", pos, line);
			++found;
		}

	return found;
}

int getline(char s[], int lim)
{
	int c, i;
	i = 0;

	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';

	return i;
}

int strindex(char s[], char t[])
{
	int i, j, k;
	int pos = -1;

	for (i = 0; s[i] != '\0'; ++i) {
		for (j = i, k = 0; s[j] == t[k]; ++j, ++k)
			;
		if (k > 0 && t[k] == '\0' && i > pos)
			pos = i;
	}

	return pos;
}