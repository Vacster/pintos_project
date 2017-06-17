#include <stdio.h>

/* Size of array to sort. */
#define SORT_SIZE 25600

int
main (void)
{
  /* Array to sort.  Static to reduce stack usage. */
  static int array[SORT_SIZE];

  int i, j, tmp;

  /* First initialize the array in descending order. */
  for (i = 0; i < SORT_SIZE; i++)
    array[i] = SORT_SIZE - i - 1;

  /* Then sort in ascending order. */
  for (i = 0; i < SORT_SIZE - 1; i++)
    for (j = 0; j < SORT_SIZE - 1 - i; j++)
      if (array[j] > array[j + 1])
	{
	  tmp = array[j];
	  array[j] = array[j + 1];
	  array[j + 1] = tmp;
	}
  return array[0];
}
