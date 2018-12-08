#include <stdio.h>

/* Write a program to print a histogram of the frequencies of different characters in its input */

#define MAX 122
#define MIN 97
#define DIFF 32

int main()
{
	int c, nc;
	int array[MAX - MIN];

	while ((c = getchar()) != EOF)
	{
		if (c >= MIN)
			++array[c];
		else
			++array[c + DIFF];
	}

	for (int i = MIN; i <= MAX; ++i) {
		printf("|%c%c|", i - DIFF, i);
		for (int j = 1; j <= array[i]; ++j) {
			printf("*");
		}
		putchar('\n');
	}

	return 0;
}
