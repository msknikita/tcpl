#include <stdio.h>

/* Write a program to print a histogram of the lengths of words in its input */

#define MAXWORDLENGTH 10
#define IN 1
#define OUT 0

int main()
{
	int c, state = IN, nc = 0;
	int array[MAXWORDLENGTH + 1];

	for (int i = 0; i <= MAXWORDLENGTH; ++i)
		array[i] = 0;

	while ((c = getchar()) != EOF) {
		++nc;
		if (c == ' ' || c == '\n' || c == '\t') {
			state = OUT;
			--nc;
		}
		if (state == OUT) {
			if (nc != 0 && nc <= MAXWORDLENGTH)
				++array[nc];
			state = IN;
			nc = 0;
		}
	}

	for (int i = 1; i <= MAXWORDLENGTH; ++i)
	{
		printf("|%2d| ", i);
		for (int j = 0; j < array[i]; ++j)
			putchar('+');

		putchar('\n');
	}

	return 0;
}
