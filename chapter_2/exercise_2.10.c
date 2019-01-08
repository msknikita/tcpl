#include<stdio.h>

/* Rewrite the function lower, which converts upper case letters to lower case, with a conditional expression instead of if-else */

int lower(char c);

int main()
{
	char c = 'B';
	printf("%d\n", lower(c));

	return 0;
}

int lower(char c)
{
	return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}