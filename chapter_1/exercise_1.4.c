#include <stdio.h>

int main()
{
	/* Write a program to print the corresponding Celsius to Fahrenheit table. */

	float fahr, celsius;
	int step, lower, upper;

	step = 20;
	lower = 0;
	upper = 300;

	celsius = lower;
	while (celsius <= upper)
	{
		fahr = (9.0 * celsius) / 5.0 + 32;
		printf("%3.0f%6.1f\n", celsius, fahr);
		celsius += step;
	}
	
	return 0;
}