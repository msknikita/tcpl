/* Write a program to compare two files, printing the first line where they differ. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 100

void filecomp(FILE *, FILE *);

int main(int argc, char *argv[])
{
	FILE *fp1, *fp2;
	
	if (argc != 3) {
		fprintf(stderr, "comp: need to specify two names of files\n");
		exit(1);
	}
	else {
		if ((fp1 = fopen(*++argv, "r")) == NULL) {
			fprintf(stderr, "comp: can't open %s\n", *argv);
			exit(1);
		}
		else if ((fp2 = fopen(*++argv, "r")) == NULL) {
			fprintf(stderr, "comp: can't open %s\n", *argv);
			exit(1);
		}
		else {
			filecomp(fp1, fp2);
			fclose(fp1);
			fclose(fp2);
			exit(0);
		}
	}
}

void filecomp(FILE *fp1, FILE *fp2)
{
	char line1[MAXLINE], line2[MAXLINE];
	char *lp1, *lp2;

	do {
		lp1 = fgets(line1, MAXLINE, fp1);
		lp2 = fgets(line2, MAXLINE, fp2);
		if (lp1 == line1 && lp2 == line2) {
			if (strcmp(line1, line2) != 0) {
				printf("Differences found in the string\n%s\n", line1);
				lp1 = lp2 = NULL;
			}
		}
		else if (lp1 != line1 && lp2 == line2)
			printf("The end first file in the string\n%s\n", line2);
		else if (lp1 == line1 && lp2 != line2)
			printf("The end second file in the string\n%s\n", line2);
	} while (lp1 == line1 && lp2 == line2);
}
