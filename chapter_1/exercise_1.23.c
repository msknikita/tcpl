#include<stdio.h>

/* Write a program to remove all comments from a C program */

#define MAXLINE 1000 
#define TRUE 1
#define FALSE 0

char line[MAXLINE];

int getLine(void);

int main(void)
{
	int length, i, in_c = FALSE, in_q = FALSE;

	while ((length = getLine()) > 0) {
		i = 0;
		while (i < length)
		{
			if (line[i] == '"')
				in_q = TRUE;
			if (!in_q)
			{
				if (line[i] == '/' && line[i + 1] == '*') {
					i += 2;
					in_c = TRUE;
				}
				if (line[i] == '*' && line[i + 1] == '/') {
					i += 2;
					in_c = FALSE;
				}
				if (in_c == TRUE)
					++i;
				else {
					printf("%c", line[i]);
					++i;
				}
			}
			else {
				printf("%c", line[i]);
				++i;
			}
		}
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