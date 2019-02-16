/* Write a function undef that will remove a name and definition from the table maintained by lookup and install */

#include <stdio.h>
#include <stdlib.h>

#define HASHSIZE 101

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
char *strdup(char *);
void undef(char *);

static struct nlist *hashtab[HASHSIZE];


struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

int main()
{
	int i;

	struct nlist *table[4] = {
		install("key1","value1"),
		install("key2","value2"),
		install("key3","value3"),
		install("key2","value2"),
	};

	for (i = 0; i < 4; ++i)
		printf("%s->%s\n", table[i]->name, table[i]->defn);

	undef("key1");
	undef("key3");

	struct nlist *result;

	char *keys[4] = {
			"key1",
			"key2",
			"key3",
			"key4"
	};

	printf("\n");

	for (i = 0; i < 4; i++) {
		if ((result = lookup(keys[i])) == NULL) {
			printf("key not found\n");
		}
		else {
			printf("%s->%s\n", result->name, result->defn);
		}
	}

	return 0;
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
