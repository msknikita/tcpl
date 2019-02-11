/* Add a field-handling capability, so sorting may be done on fields within lines,
 * each field sorted according to an independent set of options. 
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NUMERIC   1
#define DECR      2
#define LINES     100
#define FOLD      4
#define DIR       8

int numcmp(char *, char *);
int readlines(char *lineptr[], int);
void quicksort(void *v[], int, int, int(*comp)(void *, void *));
void writelines(char *lineptr[], int, int);
int charcmp(char *, char *);
void readargs(int argc, char *argv[]);
void error(char *);

static char option = 0;
int bpos = 0;
int epos = 0;

int main(int argc, char *argv[])
{
	char *lineptr[LINES];
	int nlines;     
	int  rc = 0;

	readargs(argc, argv);

	if ((nlines = readlines(lineptr, LINES)) > 0)
	{
		if (option & NUMERIC)
			quicksort((void **)lineptr, 0, nlines - 1, (int(*)(void *, void *))numcmp);
		else
			quicksort((void **)lineptr, 0, nlines - 1, (int(*)(void *, void *))charcmp);

		writelines(lineptr, nlines, option & DECR);
	}
	else
	{
		printf("input too big to sort \n");
		rc = -1;
	}

	return rc;
}

void readargs(int argc, char *argv[])
{
	int c;
	int atoi(char *);

	while (--argc > 0 && (c = (*++argv)[0]) == '-' || c == '+')
	{
		if (c == '-' && !isdigit(*(argv[0] + 1)))
			while (c = *++argv[0])
				switch (c)
				{
				case 'd':   
					option |= DIR;
					break;
				case 'f':
					option |= FOLD;
					break;
				case 'n':
					option |= NUMERIC;
					break;
				case 'r':
					option |= DECR;
					break;
				default:
					printf("sort: illegal option %c \n", c);
					error("Usage: sort -dfnr [+bpos] [-epos]");
					break;
				}

		else if (c == '-')
			epos = atoi(argv[0] + 1);
		else if ((bpos = atoi(argv[0] + 1)) < 0)
			error("Usage: sort -dfnr [+bpos][-epos]");
	}

	if (argc || bpos > epos)
		error("Usage: sort -dfnr [+bpos] [-epos]");
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

#include <math.h>

#define MAXSTR 100

void substr(char *s, char *t);

int numcmp(char *s1, char *s2)
{
	double v1, v2;
	char str[MAXSTR];

	substr(s1, str, MAXSTR);
	v1 = atof(str);

	substr(s2, str, MAXSTR);
	v2 = atof(str);

	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int charcmp(char *s, char *t)
{
	char a, b;
	int i, j, endpos;

	int fold = (option & FOLD) ? 1 : 0;
	int dir = (option & DIR) ? 1 : 0;

	i = j = bpos;

	if (epos > 0)
		endpos = epos;
	else if ((endpos = strlen(s)) > strlen(t))
		endpos = strlen(t);

	do
	{
		if (dir)
		{
			while (i < endpos && !isalnum(s[i]) && s[i] != ' ' && s[i] != '\0')
				s[i] != ' ' && s[i] != '\0';
			i++;
			while (j < endpos && !isalnum(t[j]) && t[j] != ' ' && t[j] != '\0')
				t[j] != ' ' && t[j] != '\0';
			j++;
		}
		if (i < endpos && j < endpos)
		{
			a = fold ? tolower(s[i]) : s[i];
			i++;
			b = fold ? tolower(t[j]) : t[j];
			j++;

			if (a == b && a == '\0')
				return 0;
		}
	} while (a == b && i < endpos && j < endpos);

	return a - b;
}

void substr(char *s, char *str)
{
	int i, j, len;
	extern int bpos, epos;

	len = strlen(s);

	if (epos > 0 && len > epos)
		len = epos;
	else if (epos > 0 && len < epos)
		error("substr: string too short");

	for (j = 0, i = bpos; i < len; i++, j++)
		str[j] = str[i];

	str[j] = '\0';
}

void error(char *s)
{
	printf("%s \n", s);
	exit(1);
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
