#include<stdio.h>

/* Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted, leaving the others unchanged */

void printbit(unsigned n);
unsigned invert(unsigned x, int p, int n);

int main()
{
	unsigned c1 = 'f';

	printf("76543210\n\n");
	printbit(c1);
	printbit(invert(c1, 5, 3));

	return 0;
}

unsigned invert(unsigned x, int p, int n)
{
	return (((~x >> (p + 1 - n)) & ~(~0 << n)) << (p + 1 - n)) | (~(((~0 >> (p + 1 - n)) & ~(~0 << n)) << (p + 1 - n)) & x);
}

void printbit(unsigned n)
{
	int i;
	for (i = 7; i >= 0; --i)
		printf("%d", (n >> i) & 1);

	printf("\n");
}