#include<stdio.h>

/* Write the function htoi(s), which converts a string of hexadecimal digits(including an optional 0x or 0X) into its equivalent integer value */

#define TRUE 1
#define FALSE 0
#define MAXLINE 100

int htoi(char s[]);
int getLine(char s[], int lim);

int main()
{
	char line[MAXLINE];
	int value;

	getLine(line, MAXLINE);
	value = htoi(line);

	printf("The value of %s is %d\n", line, value);

	return 0;
}

int htoi(char s[])
{
	int hexdigit, inhex, i, n;

	i = 0;
	if (s[i] == '0') {
		++i;
		if (s[i] == 'x' || s[i] == 'X')
			++i;
	}
	
	n = 0;
	inhex = TRUE;
	for (; inhex == TRUE; ++i) {
		if (s[i] >= '0' && s[i] <= '9')
			hexdigit = s[i] - '0';
		else if (s[i] >= 'a' && s[i] <= 'f')
			hexdigit = s[i] - 'a' + 10;
		else if (s[i] >= 'A' && s[i] <= 'F')
			hexdigit = s[i] - 'A' + 10;
		else
			inhex = FALSE;
		if (inhex == TRUE)
			n = 16 * n + hexdigit;
	}

	return n;
}
int getLine(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;

	s[i] = '\0';

	return i;
}



