/* Make dcl recover from input errors. */

#include <stdio.h>
#include "main.h"

extern int prevtoken;

int main(int argc, char *argv[])
{
	while (gettoken() != EOF) {
		strcpy(datatype, token);
		out[0] = '\0';
		dcl();
		if (tokentype != '\n')
			printf("syntax error\n");
		printf("%s: %s %s\n", name, out, datatype);
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
		if (tokentype != ')')
			error_msg("error: missing ) \n");
	}
	else if (tokentype == NAME)
		strcpy(name, token);
	else
		error_msg("error: expected name or (dcl) \n");

	while ((type = gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat(out, "function returning");
		else {
			strcat(out, "array");
			strcat(out, token);
			strcat(out, "of");
		}
}

void error_msg(char *msg)
{
	printf("%s", msg);
	prevtoken = YES;
}