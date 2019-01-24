#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"

#define MAXOP 100
#define PEEK 'p'

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