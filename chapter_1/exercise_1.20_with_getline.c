#include <stdio.h>

#define MAXLINE 1000
#define TABSIZE 8

int getLine(char line[], int maxline);
void detab(char to[], char from[]);

int main()
{
	int len;
	char line[MAXLINE];
	char newline[MAXLINE];

	while ((len = getLine(line, MAXLINE)) > 0) {
		detab(newline, line);
		printf("%s", newline);
	}

	return 0;
}

int getLine(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;

	if (c == '\n') {
		s[i] = c;
		++i;
	}

	s[i] = '\0';

	return i;
}

void detab(char to[], char from[])
{
	int k, i = 0, j = 0;

	while ((to[j] = from[i]) != '\0') {
		if (to[j] == '\t')
			for (k = 0; k < TABSIZE; ++k)
				to[j] = '#';
		else
			++j;
		++i;
	}

	to[j] = '\0';
}
