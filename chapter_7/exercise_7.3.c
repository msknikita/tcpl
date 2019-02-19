/* Revise minprintf to handle more of the other facilities of printf. */

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#define LOCALFMT 100

void minpintf(char *, ...);

int main()
{	
	int i = 12;
	double f = 12.0;
	char *s = "string";

	minpintf("%d %i %u %f %s %c\n", i, i, i, f, s, 'e');

	return 0;
}

void minpintf(char *fmt, ...)
{
	va_list ap;
	char *p, *sval;
	int i, ival;
	double dval;
	unsigned uval;
	char localfmt[LOCALFMT];

	va_start(ap, fmt);

	for (p = fmt; *p; ++p) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}

		i = 0;
		localfmt[i++] = '%';

		while (*(p + 1) && !isalpha(*(p + 1)))
			localfmt[i++] = *++p;

		localfmt[i++] = *(p + 1);
		localfmt[i] = '\0';

		switch (*++p) {
		case 'd':
		case 'i':
			ival = va_arg(ap, int);
			printf(localfmt, ival);
			break;
		case 'x':
		case 'X':
		case 'u':
		case 'o':
			uval = va_arg(ap, unsigned);
			printf(localfmt, uval);
			break;
		case 'f':
		case 'g':
			dval = va_arg(ap, double);
			printf(localfmt, dval);
			break;
		case 's':
			sval = va_arg(ap, char *);
			printf(localfmt, sval);
			break;
		case 'c':
			ival = va_arg(ap, int);
			putchar(ival);
			break;
		default:
			putchar(*p);
			break;
		}
	}
	va_end(ap);
}
