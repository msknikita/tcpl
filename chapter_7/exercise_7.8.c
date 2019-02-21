/* Write a program to print a set of files, starting each new one on a new page, with a title and a running page count for each file. */

#include <stdio.h>
#include <stdlib.h>

#define LINES_PER_PAGE 10
#define TRUE           1
#define FALSE          0

void printfile(char *);

int main(int argc, char *argv[])
{
	int i;

	if (argc < 2) {
		fputs("no files specified\n", stderr);
		return EXIT_FAILURE;
	}

	for (i = 1; i < argc; ++i) {
		printfile(argv[i]);
	}

	return EXIT_SUCCESS;
}

void printfile(char *fname)
{
	FILE *fp;
	int c, line_count, page_number = 1, new_page = TRUE;

	if ((fp = fopen(fname, "r")) != NULL) {
		while ((c = fgetc(fp)) != EOF) {
			if (new_page) {
				printf("[%s] page %d starts\n", fname, page_number);
				new_page = FALSE;
				line_count = 1;
			}
			putchar(c);
			if (c == '\n' && ++line_count > LINES_PER_PAGE) {
				printf("[%s] page %d ends\n", fname, page_number);
				putchar('\n');
				new_page = TRUE;
				++page_number;
			}
		}

		if (!new_page)
			printf("[%s] page %d ends\n", fname, page_number);

		putchar('\n');
		fclose(fp);
	}
}
