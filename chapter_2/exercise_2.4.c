#include<stdio.h>

/* Write a function squeeze(s1,s2) that deletes each character in the string s1 that matches any character in the string s2 */

void squeeze(char f[], char s[]);
char in_string(char c, char s[]);

int main()
{
	char s1[] = "helko";
	char s2[] = "eo";

	printf("input:  %s\n", s1);
	squeeze(s1, s2);
	printf("output: %s\n", s1);

	return 0;
}

void squeeze(char s1[], char s2[]) {
	int i, j;

	i = j = 0;
	for (; s1[i] != '\0'; ++i) {
		if (!in_string(s1[i], s2)) {
			s1[j++] = s1[i]; 
		}
	}
	s1[j] = '\0';
}

char in_string(char c, char s2[]) {
	int i = 0;

	while (s2[i] != '\0') {
		if (s2[i++] == c)
			return 1;
	}
	return 0;
}