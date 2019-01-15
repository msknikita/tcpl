/* Write a version of itoa_ that accepts three arguments instead of two. The third argument is a minimum field width; 
 * the converted number must be padded with blanks on the left if necessary to make it wide enough. 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 256

void itoa_(int n, char s[], int width);
void reverse(char s[]);

int main()
{
	char buffer[MAXLEN];
	int i = 93;

	itoa_(i, buffer, 4);
	printf("%s\n", buffer);

	return 0;
}

void itoa_(int n, char s[], int width)
{
	int i, sign;

	sign = n;
	i = 0;

	do {
		s[i++] = abs(n % 10) + '0';
		if (i > width) {
			printf("String representation is too short!\n");
			break;
		}
	} while (n /= 10);

	if (sign < 0)
		s[i++] = '-';

	while (i < width)
		s[i++] = ' ';
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