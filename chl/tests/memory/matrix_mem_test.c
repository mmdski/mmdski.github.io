#include <chl.h>
#include <stdlib.h>

int
test_matrix_new ()
{
  ChlMatrix m = chl_matrix_new (2, 2);
  return chl_matrix_free (m);
}

int
test_matrix_zeros ()
{
  ChlMatrix m = chl_matrix_zeros (2, 2);
  return chl_matrix_free (m);
}

int
test_matrix_eye ()
{
  ChlMatrix m = chl_matrix_eye (3);
  return chl_matrix_free (m);
}

void
test_matrix_mult ()
{
  // square identity matrices
  ChlMatrix a = chl_matrix_eye (3);
  ChlMatrix b = chl_matrix_eye (3);

  ChlMatrix c = chl_matrix_mult (a, b);

  chl_matrix_free (a);
  chl_matrix_free (b);
  chl_matrix_free (c);
}

int
main (int argc, char *argv[])
{
  test_matrix_new ();
  test_matrix_zeros ();
  test_matrix_eye ();
  test_matrix_mult ();
}
