#include<stdio.h>

/* 
 * Write a program to remove all trailing blanks and tabs from each line of input,
 * and to delete entirely blank lines 
 */

#define MAXLINE 1000 

char line[MAXLINE];

int getLine(void);  
int cremove(char s[]);

int main(void)
{
	int c;

	while ((c = getLine()) > 0) {
		if (cremove(line) > 0)
			printf("%s", line);
	}

	return 0;
}

int getLine(void)
{
	int c, i;	
	extern char line[];

	for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n') {
		line[i] = c;
		++i;
	}
	line[i] = '\0';

	return i;
}

int cremove(char s[])
{
	int i = 0;

	while (s[i] != '\n')
		++i;
	--i;
	while (i >= 0 && (s[i] == '\t' || s[i] == ' '))
		--i;

	if (i >= 0) {
		++i;
		s[i] = '\n';
		++i;
		s[i] = '\0';
	}

	return i;
}