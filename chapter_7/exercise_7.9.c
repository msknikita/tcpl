/* Functions like isupper can be implemented to save space or to save time. Explore both possibilities. */

#include <stdio.h>

#define isupper_time(c) ( (c) >= 'A' && (c) <= 'Z' ) ? 1 : 0

int isupper_memory(char);

int main(void)
{

	return 0;
}

int isupper_memory(char c)
{
	if (c >= 'A' && c <= 'Z')
		return 1;
	else
		return 0;
}