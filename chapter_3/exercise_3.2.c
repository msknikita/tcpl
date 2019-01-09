#include<stdio.h>

/* Write a function escape(s,t) that converts characters like newline and tab into visible escape sequences like \n and \t as it copies the string t to s. 
 * Use a switch. Write a function for the other direction as well, converting escape sequences into the real characters 
*/

#define MAXLEN 30

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main()
{
	char input[MAXLEN] = "foo\tfoo\nfoo\n";
	char output[MAXLEN];
	for (int i = 0; i < MAXLEN; ++i)
		output[i] = 0;

	printf("%s\n", input);
	escape(output, input);
	printf("%s\n", output);
	unescape(input, output);
	printf("%s\n", input);

	return 0;
}

void escape(char s[], char t[])
{
	int i, j;

	for (i = j = 0; t[i] != '\0'; ++i) {
		switch (t[i]) {
		case '\n':
			s[j++] = '\\';
			s[j++] = 'n';
			break;
		case '\t':
			s[j++] = '\\';
			s[j++] = 't';
			break;
		default:
			s[j++] = t[i];
			break;
		}
		s[j] = '\0';
	}
}

void unescape(char s[], char t[])
{
	int i, j;

	for (i = j = 0; t[i] != '\0'; ++i) {
		switch (t[i]) {
		case '\\':
			switch (t[++i]) {
			case 'n':
				s[j++] = '\n';
				break;
			case 't':
				s[j++] = '\t';
				break;
			default:
				s[j++] = t[i];
				break;
			}
		default:
			s[j++] = t[i];
			break;
		}
		s[j] = '\0';
	}
}