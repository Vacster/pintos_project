/* Shuffles a 128 kB data buffer 10 times, printing the checksum
   after each time. */

#include <random.h>
#include <stdio.h>

#define SIZE (128 * 1024)

static char buf[SIZE];
void shuffle (void *, size_t cnt, size_t size);
void swap (void *a_, void *b_, size_t size);

int
main (void)
{
  size_t i;

  /* Initialize. */
  for (i = 0; i < sizeof buf; i++)
    buf[i] = i * 257;

  /* Shuffle repeatedly. */
  for (i = 0; i < 10; i++)
    {
      shuffle (buf, sizeof buf, 1);
    }
}

void
shuffle (void *buf_, size_t cnt, size_t size)
{
  char *buf = buf_;
  size_t i;

  for (i = 0; i < cnt; i++)
    {
      size_t j = i + random_ulong () % (cnt - i);
      swap (buf + i * size, buf + j * size, size);
    }
}

void
swap (void *a_, void *b_, size_t size)
{
  uint8_t *a = a_;
  uint8_t *b = b_;
  size_t i;

  for (i = 0; i < size; i++)
    {
      uint8_t t = a[i];
      a[i] = b[i];
      b[i] = t;
    }
}
