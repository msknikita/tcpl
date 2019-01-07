#include<stdio.h>
#include<limits.h>

/* Write a function rightrot(x,n) that returns the value of the integer x rotated to the right by n bit positions */

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
	int left_shift = ((sizeof x) * CHAR_BIT) - n;

	return x << left_shift | x >> n;
}

void printbit(unsigned n)
{
	int i;
	for (i = 7; i >= 0; --i)
		printf("%d", (n >> i) & 1);

	printf("\n");
}