/* Write the function itob(n,s,b) that converts the integer n into a base b character representation in the string s.
 * In particular, itob(n,s,16) formats n as a hexadecimal integer in s.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 256

void itob(int n, char s[], int b);
void reverse(char s[]);

int main()
{
	char buffer[MAXLEN];
	int i = 93;

	itob(i, buffer, 8);
	printf("%d\n%s\n", i, buffer);

	return 0;
}

void itob(int n, char s[], int b)
{
	int i, sign;
	char digits[] = "0123456789ABCDEF";

	sign = n;

	i = 0;
	do
		s[i++] = digits[n % b];
	while (n /= b);
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