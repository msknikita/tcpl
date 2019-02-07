/* Write the program expr, which evaluates a reverse Polish expression from the command line, where each operator or operand is a separate argument.
 * For example, expr 2 3 4 + * evaluates 2 * (3 + 4).
 */

#include<stdio.h>
#include<math.h>  

#define MAXOP 100   
#define NUMBER '0'  

int getop(char[]);
void ungets(char[]);
void push(double);
double pop(void);

int main(int argc, char *argv[])
{
	char s[MAXOP];
	double op2;

	while (--argc > 0)
	{
		ungets(" ");
		ungets(*++argv);

		switch (getop(s))
		{
		case NUMBER:
			push(atoi(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor \n");
			break;
		default:
			printf("error: unknown command %s \n", s);
			argc = 1;
			break;
		}
	}
	printf("\t %8g\n", pop());

	return 0;
}

#include<ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t');

	s[1] = '\0';

	if (!isdigit(c) && c != '.')
		return c;

	i = 0;

	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()));

	if (c == '.')
		while (isdigit(s[++i] = c = getch()));

	s[i] = '\0';

	if (c != EOF)
		ungetch(c);

	return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters \n");
	else
		buf[bufp++] = c;
}

#define MAXVAL 100 

int sp = 0;
double val[MAXVAL];

void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g \n", f);
}

double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty \n");
		return 0.0;
	}
}

#include<string.h>

void ungets(char s[])
{
	int len = strlen(s);
	void ungetch(int);

	while (len > 0)
		ungetch(s[--len]);
}