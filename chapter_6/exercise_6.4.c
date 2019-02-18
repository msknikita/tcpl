/* Write a program that prints the distinct words in its input sorted into decreasing order of frequency of occurrence. 
 * Precede each word by its count.
 */

#include <stdio.h>
#include <ctype.h>

#define MAXWORD   100
#define NDISTINCT 1000

struct tnode                    
{
	char *word;                    
	int count;
	struct tnode *left;   
	struct tnode *right;  
};

struct tnode *addtree(struct tnode *, char *);
void treestore(struct tnode *);
int getword(char *, int);
void sortlist(void);

struct tnode *list[NDISTINCT];
int ntn = 0;

int main()
{
	struct tnode *root;
	char word[MAXWORD];
	int i;

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);

	treestore(root);
	sortlist();

	for (i = 0; i < ntn; ++i)
		printf("%2d:%5s\n", list[i]->count, list[i]->word);

	return 0;
}

struct tnode *talloc(void);
char *strdup(char *s);

struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	}
	else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);

	return p;
}

void treestore(struct tnode *p)
{
	if (p != NULL) {
		treestore(p->left);
		if (ntn < NDISTINCT)
			list[ntn++] = p;
		treestore(p->right);
	}
}

void sortlist(void)
{
	int gap, i, j;
	struct tnode *temp;

	for (gap = ntn / 2; gap > 0; gap /= 2)
		for (i = gap; i < ntn; ++i)
			for (j = i - gap; j >= 0; j -= gap) {
				if ((list[j]->count) >= (list[j + gap]->count))
					break;
				temp = list[j];
				list[j] = list[j + gap];
				list[j + gap] = temp;
			}
}

struct tnode *talloc(void)
{
	return(struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s) + 1);

	if (p != NULL)
		strcpy(p, s);
	return p;
}

int getword(char *word, int lim)
{
	int c, d;
	int getch(void);
	void ungetch(int);
	int in_comment(void);
	char *w = word;

	while (isspace(c = getch()) && c != '\n')
		;
	if (c != EOF)
		*w++ = c;
	if (isalpha(c) || c == ' ' || c == '#')
	{
		for (; --lim > 0; w++)
			if (!isalnum(*w = getch()) && *w != '_')
			{
				ungetch(*w);
				break;
			}
	}
	else if (c == '\'' || c == '"')
	{
		for (; --lim > 0; w++)
			if ((*w = getch()) == '\\')
				*++w = getch();
			else if (*w == c)
			{
				w++;
				break;
			}
			else if (*w == EOF)
				break;
	}
	else if (c == '/')
	{
		if (((d = getch()) == '*'))
			c = in_comment();
		else
			ungetch(d);
	}
	*w = '\0';
	return c;
}

int in_comment(void)
{
	int c;

	while ((c = getch()) != EOF)
		if (c == '*')
		{
			if ((c = getch()) == '/')
				break;
			else
				ungetch(c);
		}
	return c;
}
