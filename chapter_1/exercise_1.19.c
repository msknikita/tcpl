#include <stdio.h>

/* Write a function reverse(s) that reverses the character string s */

#define MAXLINE 1000

int getLine(char line[], int maxline);
void reverse(char s[]);

int main()
{
	int len;
	char line[MAXLINE];

	while ((len = getLine(line, MAXLINE)) > 0) {
		reverse(line);
		printf("%s", line);
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

void reverse(char s[])
{
	int j = 0, i = 0, tmp;

	while (s[i] != '\0')
		++i;
	--i;
	if (s[i] == '\n')
		--i;

	while(j < i) {
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
		++j;
		--i;
	}
}
