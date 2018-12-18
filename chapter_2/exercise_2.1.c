#include<stdio.h>
#include<limits.h>
#include<float.h>

/* Write a program to determine the ranges of char, short, int, and long variables, both signed and unsigned,
 * by printing appropriate values from standard headers and by direct computation 
 */ 

int main(void)
{
	/* 1 */
	printf("%d <= char <= %d\n", SCHAR_MIN, SCHAR_MAX);
	printf("%d <= int <= %d\n", INT_MIN, INT_MAX);
	printf("%ld <= long <= %ld\n", LONG_MIN, LONG_MAX);
	printf("%d <= short <= %d\n", SHRT_MIN, SHRT_MAX);
	printf("0 <= unsigned char <= %d\n", UCHAR_MAX);
	printf("0 <= unsigned int <= %u\n", UINT_MAX);
	printf("0 <= unsigned long <= %lu\n", ULONG_MAX);
	printf("0 <= unsigned short <= %d\n", USHRT_MAX);
	printf("\n");

	/* 2 */
	printf("char min = %d\n", -(char)((unsigned char)~0 >> 1) - 1);
	printf("char max = %d\n", (char)((unsigned char)~0 >> 1));
	printf("int min = %d\n", -(int)((unsigned int)~0 >> 1) - 1);
	printf("int max = %d\n", (int)((unsigned int)~0 >> 1));
	printf("long min = %ld\n", -(long)((unsigned long)~0 >> 1) - 1);
	printf("long max = %ld\n", (long)((unsigned long)~0 >> 1));
	printf("short min = %d\n", -(short)((unsigned short)~0 >> 1) - 1);
	printf("short max = %d\n", (short)((unsigned short)~0 >> 1));
	printf("unsigned char = %d\n", (unsigned char)~0);
	printf("unsigned int = %u\n", (unsigned int)~0);
	printf("unsigned long = %lu\n", (unsigned long)~0);
	printf("unsigned short = %d\n", (unsigned short)~0);

	int x;
	float y;

	for (x = 1; x > x - 1; ++x)
		if (x < 0)
			break;

	printf("\n");
	printf("int min = %d\n", x);
	printf("int max = %d\n", --x);

	printf("\n");
	for (y = 1; y > y / 2; y *= 2)
		printf("%e\n", y);
	   
	return 0;
}


