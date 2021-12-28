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

  int       n   = 3;
  ChlMatrix eye = chl_matrix_eye (n);
  real      value;
  for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= n; j++)
        {
          if (chl_matrix_get (eye, i, j, &value) < 0)
            goto fail;
          printf ("%f\n", value);
        }
    }

  chl_matrix_free (eye);

  return EXIT_SUCCESS;

fail:
  chl_matrix_free (eye);
  return EXIT_FAILURE;
}
