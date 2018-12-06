#include <stdio.h>

/* Press Ctrl-D (end of file) to obtain 0, or press any key and then <enter> for 1 */

int main()
{	
	int c;

	while (c = getchar() != EOF)
	{
		printf("%d\n", c);
	}
	printf(%d - at EOF\n, c);

	return 0;
}