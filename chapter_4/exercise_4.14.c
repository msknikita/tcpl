/* Define a macro swap(t,x,y) that interchanges two arguments of type t. */

#include <stdio.h>

#define swap(t, x, y) {t z; z = x; x = y; y = z;}

int main()
{
	int a = 1, b = 2;
	printf("a=%d, b=%d\n", a, b);
	swap(int, a, b);
	printf("a=%d, b=%d\n", a, b);

	return 0;
}
