/* In a two's complement number representation, our version of itoa does not handle the largest negative number, that is, the value of n equal to -(2 to the power (wordsize - 1)).
 * Modify it to print that value correctly regardless of the machine on which it runs. 
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define MAXLEN 256

void itoa(int n, char s[]);
void reverse(char s[]);

int main()
{
	char buffer[MAXLEN];
	int i = 40;

	itoa(i, buffer);
	printf("%d\n%s\n", i, buffer);
	printf("\n");
	itoa(INT_MIN, buffer);
	printf("%d\n%s\n", INT_MIN, buffer);

	return 0;
}

void itoa(int n, char s[])
{
	int i, sign;

	sign = n;

	i = 0;
	do
		s[i++] = abs(n % 10) + '0';
	while (n /= 10);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}
void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; ++i, --j) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}





