/* An alternate organization uses getline to read an entire input line; this makes getch and ungetch unnecessary.
 * Revise the calculator to use this approach.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define PEEK 'p'
#define MAXLINE 100

int getop(char s[]);
void push(double);
double pop(void);
void clear(void);

int main()
{
	int type, i, var = 0;
	double op1, op2, v = 0.0;
	char s[MAXOP];
	double variable[26];

	for (i = 0; i < 26; ++i)
		variable[i] = 0.0;

	while ((type = getop(s)) != EOF) {
		switch (type)
		{
		case NUMBER:
			push(atof(s));
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
				printf("error: zero divisor\n");
			break;
		case '%':
			op2 = pop();
			if (op2 != 0.0) {
				op1 = pop();
				push(op1 - op2 * floor(op1 / op2));
			}
			else
				printf("Error: division by zero");
			break;
		case PEEK:
			op2 = pop();
			printf("\t%.8g\n", op2);
			push(op2);
			break;
		case 'd':
			op2 = pop();
			push(op2);
			push(op2);
			break;
		case 'c':
			clear();
			break;
		case 's':
			op1 = pop();
			op2 = pop();
			push(op1);
			push(op2);
			break;
		case 'w':
			op2 = pop();
			if (op2 > 0) {
				op1 = pop();
				if (op1 != 0)
					push(pow(op1, op2));
				else
					printf("domain error: x = 0\n");
			}
			else
				printf("domain error: y <= 0\n");
			break;
		case '=':
			pop();
			if (var >= 'A' && var <= 'Z')
				variable[var - 'A'] = pop();
			else
				printf("error: novariablename\n");
			break;
		case '\n':
			v = pop();
			printf("\t%.8g\n", v);
			break;
		default:
			if (type >= 'A'&&type <= 'Z')
				push(variable[type - 'A']);
			else if (type == 'v')
				push(v);
			else
				printf("error: unknown command %s\n", s);
			break;
		}
		var = type;
	}

	return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

void clear(void)
{
	sp = 0;
}

#include <ctype.h>

int getline(char s[], int lim);

char line[MAXLINE];
int li = 0;

int getop(char s[])
{
	int i, c;

	if (line[li] == '\0')
		if (getline(line, MAXLINE) == 0)
			return EOF;
		else
			li = 0;

	while ((s[0] = c = line[li++]) == ' ' || c == '\t');
	
	s[1] = '\0';

	if (!isdigit(c) && c != '.')
		return c;

	i = 0;

	if (isdigit(c))
		while (isdigit(s[++i] = c = line[li++]));

	if (c == '.')
		while (isdigit(s[++i] = c = line[li++]));

	s[i] = '\0';

	li--;

	return NUMBER;
}
int getline(char s[], int lim)
{
	int c, i;
	i = 0;

	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;

	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';

	return i;
}
