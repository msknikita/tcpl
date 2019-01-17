/* Extend atof to handle scientific notation of the form 123.45e-6 where a floating-point number may be followed by e or E and an optionally signed exponent. */

#include <stdio.h>
#include <ctype.h>

#define MAXLEN 1000

double atof(char s[]);

int main()
{
	char num1[MAXLEN] = "123.45e-6";
	char num2[MAXLEN] = "-10.32e+3";

	printf("%s\n", num1);
	printf("%f\n\n", atof(num1));

	printf("%s\n", num2);
	printf("%f\n", atof(num2));

	return 0;
}

double atof(char s[])
{
	double val, power;
	int i, sign, exp;

	for (i = 0; isspace(s[i]); ++i);

	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;

	for (val = 0.0; isdigit(s[i]); ++i)
		val = 10.0 * val + (s[i] - '0');

	if (s[i] == '.')
		++i;

	for (power = 1.0; isdigit(s[i]); ++i) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}

	val = sign * val / power;

	if (s[i] == 'e' || s[i] == 'E') {
		sign = (s[++i] == '-' ? -1 : 1);
		if (s[i] == '+' || s[i] == '-')
			++i;
		for (exp = 0; isdigit(s[i]); ++i)
			exp = 10 * exp + (s[i] - '0');
		if (sign == 1)
			while (exp-- > 0)
				val *= 10;
		else
			while (exp-- > 0)
				val /= 10;
	}

	return val;
}
