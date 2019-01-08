#include<stdio.h>

/* Alternative solution */

void printbit(unsigned n);
unsigned rightrot(unsigned x, int n);

int main()
{
	unsigned c = 'f';

	printf("76543210\n\n");
	printbit(c);
	printbit(rightrot(c, 3));

	return 0;
}

unsigned rightrot(unsigned x, int n)
{
	int getLength(void);
	unsigned rbit;
	
	rbit = x << (getLength() - n);
	x = x >> n;
	x = x | rbit;

	return x;
}

int getLength(void)
{
	int i;
	unsigned v = ~0;

	for (i = 1; (v = v >> 1) > 0; ++i)
		;
	return i;
}

void printbit(unsigned n)
{
	int i;
	for (i = 7; i >= 0; --i)
		printf("%d", (n >> i) & 1);

	printf("\n");
}