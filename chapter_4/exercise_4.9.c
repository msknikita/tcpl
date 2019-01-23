/* Our getch and ungetch do not handle a pushed-back EOF correctly. 
 * Decide what their properties ought to be if an EOF is pushed back, then implement your design. 
 */

#include <stdio.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int c);

int buf[BUFSIZE];
char bufp = 0;

int main()
{
	int c;

	c = '*';

	ungetch(c);

	while ((c = getch()) != EOF)
		putchar(c);

	return 0;
}

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}