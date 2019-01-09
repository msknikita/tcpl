#include<stdio.h>
#include<time.h>

/* Our binary search makes two tests inside the loop, when one would suffice(at the price of more tests outside). 
 * Write a version with only one test inside the loop and measure the difference in run-time 
 */

#define ARRAY_SIZE 10
#define MAX_TEST 200000000

int bsearch_1(int x, int arr[], int n);
int bsearch_2(int x, int arr[], int n);

int main()
{
	int i;
	int x = 8;
	int array[ARRAY_SIZE];
	clock_t time;

	for (i = 0; i < ARRAY_SIZE; ++i) {
		array[i] = i;
		printf("%d ", array[i]);
	}
	printf("\n");

	printf("Position of %d in array = %d\n", x, bsearch_2(x, array, ARRAY_SIZE));

	for (i = 0, time = clock(); i < MAX_TEST; ++i)
		bsearch_1(x, array, ARRAY_SIZE);
	time = clock() - time;
	printf("bsearch_1() works %lu seconds\n",
		(unsigned long)time / CLOCKS_PER_SEC);

	for (i = 0, time = clock(); i < MAX_TEST; ++i)
		bsearch_2(x, array, ARRAY_SIZE);
	time = clock() - time;
	printf("bsearch_2() works %lu seconds\n",
		(unsigned long)time / CLOCKS_PER_SEC);

	return 0;
}

int bsearch_1(int x, int arr[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;

	while (low < high)
	{
		mid = (low + high) / 2;

		if (x < arr[mid])
			high = mid - 1;
		else if (x > arr[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int bsearch_2(int x, int arr[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	mid = (low + high) / 2;

	while ((low <= high) && (arr[mid] != x)) {
		mid = (low + high) / 2;
		if (x < arr[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}

	return x == arr[mid] ? mid : -1;
}
