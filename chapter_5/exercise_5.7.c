/* Rewrite readlines to store lines in an array supplied by main, rather than calling alloc to maintain storage.
 * How much faster is the program?
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000

int readlines(char *lineptr[], char *, int);
void writelines(char *lineptr[], int);
void qsort(char *lineptr[], int, int);

char *lineptr[MAXLINES];
char linestor[MAXLINES];

int main()
{
	int nlines;

	if ((nlines = readlines(lineptr, linestor, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	}
	else {
		printf("error: to many strings\n");
		return 1;
	}
}

#define MAXLEN 1000
#define MAXSTOR 5000

int getline(char s[], int lim);

int readlines(char *lineptr[], char *linestor, int maxlines)
{
	int len, nlines;
	char line[MAXLEN];
	char *p = linestor;
	char *linestop = linestor + MAXSTOR;

	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || p + len > linestop)
			return -1;
		else {
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
			p += len;
		}

	return nlines;
}

void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);

}

void qsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)
		return;
	swap(v, left, (left + right) / 2);

	last = left;

	for (i = left + 1; i <= right; ++i)
		if (strcmp(v[i], v[left]) < 0) //if v[1] less than v[0]
			swap(v, ++last, i);
	
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int getline(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;

	if (c == '\n') {
		s[i] = c;
		++i;
	}

	s[i] = '\0';

	return i;
}