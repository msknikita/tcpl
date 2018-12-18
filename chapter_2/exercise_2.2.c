#include<stdio.h>

/* Write a loop equivalent to the for loop above without using && or || */

#define LENGTH 10

int main()
{
	int i, c;
	char s[LENGTH];

	/* for (i = 0; i < LENGTH - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
	 *	s[i] = c;
	*/

	i = 0;
	while (i < LENGTH - 1) {
		c = getchar();

		if (c == EOF)
			break;

		if (c == '\n')
			break;

		s[i++] = c;
	}
	s[i] = '\0';

	printf("%s", s);

	return 0;
}

