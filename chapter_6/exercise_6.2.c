/* Write a program that reads a C program and prints in alphabetical order each group of variable names that are identical in the first 6 characters,
 * but different somewhere thereafter. Don’t count words within strings and comments. Make 6 a parameter that can be set from the command line.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

struct tnode *addtree(struct tnode*, char *);
void treeprint(struct tnode *);
int getword(char *, int);
int strncmp(char *, char *, int);

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

int num;

int main(int argc, char *argv[])
{
	struct tnode *root;
	char word[MAXWORD];

	if (argc == 2)
		num = atoi(argv[1]);
	else if (argc < 2)
		num = 3;
	else {
		printf("usage: tree <number>\n");
		exit(-1);
	}

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	treeprint(root);

	return 0;
}

int getword(char *word, int lim)
{
	int c, t, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()));
	if (c != EOF)
		*w++ = c;
	if (isalpha(c) || c == '_') {
		for (; --lim > 0; w++)
			if (!isalnum(*w = getch()) && *w != '_') {
				ungetch(*w);
				break;
			}
	}
	else if (c == '"') {
		while ((t = getch()) != c && t != EOF);
	}
	else if (c == '/') {
		if ((t = getch()) == '*') {
			while ((t = getch()) != EOF)
				if (t == '*') {
					if ((t = getch()) == '/')
						break;
					else
						ungetch(t);
				}
		}
		else
			ungetch(t);
	}

	*w = '\0';

	return c;
}

struct tnode *talloc(void);
char *strdup(char *);

struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	}
	else if ((cond = strncmp(w, p->word, num)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);

	return p;
}

int strncmp(char *s, char *t, int n)
{
	for (; *s == *t; ++s, ++t)
		if (*s == '\0' || --n <= 0)
			return 0;

	return *s - *t;
}

void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup(char *s)
{
	char *p;

	p = (char *)malloc(strlen(s) + 1);

	if (p != NULL)
		strcpy(p, s);

	return p;
}
