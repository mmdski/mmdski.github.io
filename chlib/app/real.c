#include <chl.h>
#include <stdio.h>
#include <stdlib.h>

int
main ()
{
#if defined(REAL_IS_FLOAT)
  printf ("Real is float\n");
#else
  printf ("Real is double\n");
#endif
  printf ("Size of real: %lu\n", sizeof (real));
  printf ("Size of float: %lu\n", sizeof (float));
  printf ("Size of double: %lu\n", sizeof (double));

  return EXIT_SUCCESS;
}
