/* Write a private version of scanf analogous to minprintf from the previous section. */

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#define LOCALFMT 100

void minscanf(char *, ...);

int main()
{	
	int i;
	unsigned u;
	double d;
	char s[100];

	minscanf("%d %f %u %s", &i, &d, &u, s);
	printf("%d %f %u %s\n", i, d, u, s);

	return 0;

}

void minscanf(char *fmt, ...)
{
	va_list ap;       
	char *p, *sval;
	int *ival;
	double *dval;
	unsigned *uval;

	va_start(ap, fmt); 

	for (p = fmt; *p; p++) {
		if (*p == '%') {
			switch (*++p) {
			case 'd':
			case 'i':
				ival = va_arg(ap, int *);
				scanf("%d", ival);
				break;
			case 'x':
			case 'X':
			case 'u':
			case 'o':
				uval = va_arg(ap, unsigned *);
				scanf("%u", uval);
				break;
			case 'f':
				dval = va_arg(ap, double *);
				scanf("%lf", dval);
				break;
			case 's':
				sval = va_arg(ap, char *);
				scanf("%s", sval);
				break;
			default:
				putchar(*p);
				break;
			}
		}
	}
	va_end(ap); 
}