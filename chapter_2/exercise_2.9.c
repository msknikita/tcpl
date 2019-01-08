#include<stdio.h>

/* In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit in x. Use this observation to write a faster version of bitcount */

int bitcount(unsigned x);
void print(unsigned n);

int main()
{
	unsigned c = 'g';
	print(c);
	printf("%d\n", bitcount(c));

	return 0;
}

int bitcount(unsigned x)
{
	int b;
	
	for (b = 0; x != 0; x &= (x - 1))
		b++;
	return b;
}

void print(unsigned n)
{
	int i;
	for (i = 7; i >= 0; --i) {
		printf("%d", (n >> i) & 1);
	}
	printf("\n");
}