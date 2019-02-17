/* Implement a simple version of the #define processor(no arguments) suitable for use with C programs, based on the routines of this section. 
 * You may also find getch and ungetch helpful. 
 */

#include <stdio.h>
#include <stdlib.h>

#define HASHSIZE 101
#define MAXWORD  1000

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
char *strdup(char *);
void undef(char *);
int getword(char *, int);

static struct nlist *hashtab[HASHSIZE];


struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

int main(void)
{
	int line = 0;
	char word[MAXWORD];
	char key[MAXWORD], value[MAXWORD];
	struct nlist *result;

	while (getword(word, MAXWORD) != EOF) {
		if (strcmp(word, "#define ") == 0) {
			getword(key, MAXWORD);
			getword(value, MAXWORD);
			install(key, value);
			result = lookup(key);
			printf("%s->%s", result->name, result->defn);
		}
	}

	return 0;
}

#define IN  1
#define OUT 0

int getword(char *word, int lim)
{
	int c, d, getch(void), comment, string, directive;
	void ungetch(int);
	char *w = word;

	comment = string = directive = OUT;

	while (isspace(c = getch()));

	if (c == '/') {
		if ((d = getch()) == '*')
			comment = IN;
		else {
			comment = OUT;
			ungetch(d);
		}
	}

	if (c == '\"')
		string = IN;

	if (c == '#')
		directive = IN;

	if (c == '\\')
		c = getch();

	if (comment == OUT && string == OUT && directive == OUT) {
		if (c != EOF)
			*w++ = c;

		if (!isalnum(c) && c != '_') {
			*w = '\0';
			return c;
		}

		for (; --lim > 0; ++w) {
			*w = getch();
			if (!isalnum(*w) && *w != '_') {
				ungetch(*w);
				break;
			}
		}

		*w = '\0';

		return word[0];
	}
	else if (comment == IN) {
		*w++ = c;
		*w++ = d;

		while ((*w++ = c = getch())) {
			if (c == '*') {
				if ((c = getch()) == '/') {
					*w++ = c;
					comment = OUT;
					break;
				}
				else
					ungetch(c);
			}
		}
		*w = '\0';
	}
	else if (string == IN) {
		*w++ = c;
		while ((*w++ = getch()) != '\"') {
			if (*w == '\\')
				*w++ = getch();
		}
		string = OUT;
		*w = '\0';
	}
	else if (directive == IN) {
		*w++ = c;
		while ((*w++ = getch()) != ' ') {
			if (c == '\\')
				*w++ = getch();
		}
		directive = OUT;
		*w = '\0';
	}

	return c;
}

void undef(char *s)
{
	struct nlist *found;

	found = lookup(s);

	if (found == NULL) 
		return NULL;
	else {
		if (found->next != NULL) {
			found->next = found->next->next;
			found = found->next;
		}
		else {
			hashtab[hash(s)] = NULL;
			free((void *)found);
		}
	}

	return found;
}

unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; ++s)
		hashval = *s + 31 * hashval;

	return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;

	return NULL;
}

struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	else
		free((void *)np->defn);
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;

	return np;
}

char *strdup(char *s)
{
	char *p;

	p = (char *)malloc(strlen(s) + 1);

	if (p != NULL)
		strcpy(p, s);

	return p;
}
