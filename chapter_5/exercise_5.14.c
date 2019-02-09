/* Modify the sort program to handle a -r flag, which indicates sorting in reverse(decreasing) order. 
 * Be sure that -r works with -n.
 */

#include <stdio.h>
#include <string.h>

#define NUMERIC   1 
#define DECR      2 
#define LINES     100  

int numcmp(char *, char *);
int readlines(char *lineptr[], int);
void quicksort(void *v[], int, int, int(*comp)(void *, void *));
void writelines(char *lineptr[], int, int);

static char option = 0;

int main(int argc, char *argv[])
{
	char *lineptr[LINES];
	int nlines;     
	int c, rc = 0;     

	while (--argc > 0 && (*++argv)[0] == '-')
		while (c = *++argv[0])
			switch (c) {
			case 'n': 
				option |= NUMERIC;
				break;
			case 'r': 
				option |= DECR;
				break;
			default:
				printf("sort:illegal option %c\n", c);
				argc = 1;
				rc = -1;
				break;
			}

	if (argc)
		printf("Usage: sort -nr \n");
	else
		if ((nlines = readlines(lineptr, LINES)) > 0) {
			if (option & NUMERIC)
				quicksort((void **)lineptr, 0, nlines - 1, (int(*)(void *, void *))numcmp);
			else
				quicksort((void **)lineptr, 0, nlines - 1, (int(*)(void *, void *))numcmp);

			writelines(lineptr, nlines, option & DECR);
		}
		else {
			printf("input too big to sort \n");
			rc = -1;
		}

	return rc;
}

void writelines(char *lineptr[], int nlines, int decr)
{
	int i;

	if (decr)    
		for (i = nlines - 1; i >= 0; --i)
			printf("%s\n", lineptr[i]);
	else
		for (i = 0; i < nlines; ++i)
			printf("%s\n", lineptr[i]);
}

#include<stdlib.h>

int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);

	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

#define MAXLEN 1000

int getline(char [], int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];
	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else
		{
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}


#define ALLOCSIZE 1000  

static char allocbuf[ALLOCSIZE];    
static char *allocp = allocbuf;

char *alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp - n;
	}
	else
		return 0;
}

void afree(char *p)
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

void quicksort(void *v[], int left, int right, int(*comp)(void *, void *))
{
	int i, last;
	void swap(void *v[], int, int);

	if (left >= right)
		return;

	swap(v, left, (left + right) / 2);

	last = left;

	for (i = left + 1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);

	quicksort(v, left, last - 1, comp);
	quicksort(v, last + 1, right, comp);
}

void swap(void *v[], int i, int j)
{
	void *temp;

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
