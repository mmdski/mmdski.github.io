#include <stdlib.h>

void *
chl_alloc (long nbytes)
{
  return malloc (nbytes);
}

void *
chl_calloc (long count, long nbytes)
{
  return calloc (count, nbytes);
}

void
chl_free (void *ptr)
{
  free (ptr);
}
