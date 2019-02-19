/* Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf to do the input and number conversion. */

#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100 

void push(double);
double pop(void);

int main()
{
	char *c;
	char s[MAXOP], buf[MAXOP];
	double a = 0, op2,p;
	char e = '\0';

	while ((p = scanf("%s%c", s, &e)) == 2) {
		if (sscanf(s, " %lf", &a) == 1) 
			push(a);
		else if (sscanf(s, "%s", buf)) {
			for (c = buf; *c; c++) {
				switch (*c) {
				case '+':
					push(pop() + pop());
					break;
				case '-':
					op2 = pop();
					push(pop() - op2);
					break;
				case '*':
					push(pop() * pop());
					break;
				case '/':
					op2 = pop();
					if (op2 != 0.0)
						push(pop() / op2);
					else
						printf("error: zero divisor\n");
					break;
				default:
					printf("Unknown command\n");
					break;
				}
			}
			if (e == '\n') 
				printf("\t%.8g\n", pop());
		}
	}
	return 0;
}

#define MAXVAL 100 

static int sp = 0;
static double val[MAXVAL]; 


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
