#include <stdio.h>

/* Rewrite the temperature conversion program of Section 1.2 to use a function for conversion */

#define UPPER 300
#define LOWER 0
#define STEP 20

float bar(float fahr);

int main()
{
	float fahr;

	fahr = LOWER;
	while (fahr <= UPPER) {
		printf("%3.0f  %6.1f\n", fahr, bar(fahr));
		fahr += STEP;
	}

	return 0;
}

float bar(float fahr) 
{
	return (5.0 / 9.0) * (fahr - 32);
}