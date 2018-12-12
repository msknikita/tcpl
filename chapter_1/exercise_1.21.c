#include<stdio.h>

#define MAXLINE 1000 
#define TABSIZE 4 

char line[MAXLINE];

int getLine(void);  

int main(void)
{
	int i, t;
	int scount, len;

	while ((len = getLine()) > 0)
	{
		scount = 0;
		for (i = 0; i < len; i++)
		{
			if (line[i] == ' ')
				scount++;
			if (line[i] != ' ')
				scount = 0;
			if (scount == TABSIZE)
			{
				i -= 3;
				len -= 3;
				line[i] = '\t';

				for (t = i + 1; t < len; t++)
					line[t] = line[t + 3];
				scount = 0;
				line[len] = '\0';
			}
		}
		printf("%s", line);
	}

	return 0;
}

int getLine(void)
{
	int c, i;
	extern char line[];

	for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n') {
		line[i] = c;
		++i;
	}
	line[i] = '\0';

	return i;
}