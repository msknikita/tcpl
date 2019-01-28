/* Adapt the ideas of printd to write a recursive version of itoa;
 * that is, convert an integer into a string by calling a recursive routine. 
 */

#include <stdio.h>

void itoa_(int n, char s[]);

int main()
{
	char buffer[256];
	int i = -32;

	itoa_(i, buffer);
	printf("%d\n%s\n", i, buffer);
	printf("\n");

	return 0;
}

void itoa_(int n, char s[])
{
	 static int i;

	if (n < 0) {
		n = -n;
		s[i++] = '-';
	}
	if (n / 10)
		itoa_(n / 10, s);
	s[i++] = n % 10 + '0';
	s[i] = '\0';
}