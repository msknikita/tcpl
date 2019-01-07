#include<stdio.h>

/* Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the rightmost n bits of y, 
 * leaving the other bits unchanged 
 */

unsigned setbits(unsigned x, int p, int n, unsigned y);
void printbit(unsigned n);

int main()
{
	unsigned c1 = 'f';
	unsigned c2 = 'g';

	printf("76543210\n\n");
	printbit(c1);
	printbit(c2);

	printbit(setbits(c1, 5, 3, c2));

	return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	return ((~0 << (p + 1)) & x) | (~(~0 << (p + 1 - n)) & x) | (~(~0 << n) & y) << (p + 1 - n);
}

void printbit(unsigned n)
{
	int i;
	for (i = 7; i >= 0; --i)
		printf("%d", (n >> i) & 1);

	printf("\n");
}