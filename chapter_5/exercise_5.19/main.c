/* Modify undcl so that it does not add redundant parentheses to declarations. */

#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char *argv[])
{
	int type;
	char temp[MAXTOKEN];

	while (gettoken() != EOF)
	{
		strcpy(out, token);

		while ((type = gettoken()) != '\n')
			if (type == PARENS || type == BRACKETS)
				strcat(out, token);
			else if (type == '*') {
				if ((type = nexttoken()) == PARENS || type == BRACKETS)
					sprintf(temp, "(*%s)", out);
				else
					sprintf(temp, "*%s", out);
				strcpy(out, temp);
			}
			else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			}
			else
				printf("invalid input at %s \n", token);
		printf("%s\n", out);
	}

	return 0;
}

void dcl(void)
{
	int ns;

	for (ns = 0; gettoken() == '*';)
		++ns;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

void dirdcl(void)
{
	int type;

	if (tokentype == '(') {
		dcl();
		if (tokentype != ')') {
			printf("error: missing ) \n");
			exit(-1);
		}
	}
	else if (tokentype == NAME)
		strcpy(name, token);
	else {
		printf("error: expected name or (dcl) \n");
		exit(-1);
	}

	while ((type = gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat(out, "function returning");
		else {
			strcat(out, "array");
			strcat(out, token);
			strcat(out, " of");
		}
}