/* Extend entab and detab to accept the shorthand entab -m +n to mean tab stops every n columns;
 * starting at column m. Choose convenient size for the default behaviour 
 */

#include<stdio.h>

#define MAXLINES 50 
#define NSTR 10 
#define MAXSTOR 5000

int setnumlines(int, char *[]);
int readlines(char *[], int);
void tail(char *[], int, int n);

char *lineptr[MAXLINES];

int main(int argc, char *argv[])
{
	int nlines; 
	int n; 

	n = setnumlines(argc, argv);

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		tail(lineptr, nlines, n);
		return 0;
	}
	else {
		printf("error\n");
		return 1;
	}

	return 0;
}

#define MAXLEN 1000

char *alloc(int);
int getline(char s[], int lim);

int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char line[MAXLEN];
	char *p;

	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}

	return nlines;
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

int setnumlines(int argc, char *argv[])
{
	int n;

	while (--argc > 0 && **++argv == '-') {
		if ((n = atoi(*argv + 1)) > 0)
			return n;
		else
			return 0;
	}
	return NSTR;
}

void tail(char *lineptr[], int nlines, int n)
{
	int i;

	if (n > nlines)
		n = nlines;
	for (i = 1; i <= n; i++)
		printf("%s\n", lineptr[nlines - i]);
}

#define ALLOCSIZE 10000

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
