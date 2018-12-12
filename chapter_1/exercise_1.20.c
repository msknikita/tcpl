#include <stdio.h>

/* Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop */

#define TABSIZE 8

int main()
{
	int c, nb = 0, pos = 1;

	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			nb = TABSIZE - ((pos - 1) % TABSIZE);

			while (nb > 0) {
				putchar('*');
				++pos;
				--nb;
			}
		}
		else if (c == '\n') {
			putchar(c);
			pos = 1;
		}
		else {
			putchar(c);
			++pos;
		}

	}

	return 0;
}
