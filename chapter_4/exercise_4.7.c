/* Write a routine ungets(s) that will push back an entire string onto the input. */

#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

void ungets(char s[]);
int getch(void);
void ungetch(int c);

char buf[BUFSIZE];
int bufp = 0;

int main()
{
	char line[] = "test\n";
	int c;

	ungets(line);

	while ((c = getch()) != EOF)
		putchar(c);

	return 0;
}

void ungets(char s[])
{
	int len = strlen(s);

	while (len > 0)
		ungetch(s[--len]);
}

int getch(void)
{
	return(bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}