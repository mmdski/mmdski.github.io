#include <chl.h>
#include <stdlib.h>

int
test_matrix_new ()
{
  ChlMatrix m = chl_matrix_new (2, 2);
  if (m == NULL)
    return -1;

  if (chl_matrix_free (m) < 0)
    return -1;

  return 0;
}

int
test_matrix_zeros ()
{
  ChlMatrix m = chl_matrix_zeros (2, 2);
  if (m == NULL)
    return -1;

  if (chl_matrix_free (m) < 0)
    return -1;

  return 0;
}

int
test_matrix_eye ()
{
  ChlMatrix m = chl_matrix_eye (3);
  if (m == NULL)
    return -1;

  if (chl_matrix_free (m) < 0)
    return -1;

  return 0;
}

int
test_matrix_mult ()
{
  // square identity matrices
  ChlMatrix a = chl_matrix_eye (3);
  if (a == NULL)
    return -1;

  ChlMatrix b = chl_matrix_eye (3);
  if (b == NULL)
    return -1;

  ChlMatrix c = NULL;
  if (chl_matrix_mult (a, b, &c) < 0)
    return -1;
  if (c == NULL)
    return -1;

  // test it again when c is not NULL
  if (chl_matrix_mult (a, b, &c) < 0)
    return -1;
  if (c == NULL)
    return -1;

  if (chl_matrix_free (a) < 0)
    return -1;
  if (chl_matrix_free (b) < 0)
    return -1;
  if (chl_matrix_free (c) < 0)
    return -1;

  return 0;
}

int
main (int argc, char *argv[])
{
  if (test_matrix_new () < 0)
    return EXIT_FAILURE;
  if (test_matrix_zeros () < 0)
    return EXIT_FAILURE;
  if (test_matrix_eye () < 0)
    return EXIT_FAILURE;
  if (test_matrix_mult () < 0)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
