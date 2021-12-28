#include <chl.h>
#include <glib.h>

void
test_matrix_new ()
{
  int n_rows    = 3;
  int n_columns = 3;

  ChlMatrix m = chl_matrix_new (n_rows, n_columns);
  g_assert_nonnull (m);
  chl_matrix_free (m);

  // test failures
  m = NULL;
  m = chl_matrix_new (-1, -1);
  g_assert_null (m);

  m = NULL;
  m = chl_matrix_new (n_rows, -1);
  g_assert_null (m);

  m = NULL;
  m = chl_matrix_new (-1, n_columns);
  g_assert_null (m);
}

void
test_matrix_zeros ()
{
  int n_rows    = 3;
  int n_columns = 3;

  ChlMatrix m = chl_matrix_zeros (n_rows, n_columns);

  real value;

  for (int i = 1; i <= n_rows; i++)
    {
      for (int j = 1; j <= n_columns; j++)
        {

          chl_matrix_get (m, i, j, &value);
          g_assert_cmpfloat_with_epsilon (value, 0, 1e-10);
        }
    }

  chl_matrix_free (m);
}

void
test_matrix_eye ()
{
  int n = 3;

  ChlMatrix m = chl_matrix_eye (n);

  real value;
  real expected;

  for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= n; j++)
        {
          if (i == j)
            expected = 1;
          else
            expected = 0;

          chl_matrix_get (m, i, j, &value);
          g_assert_cmpfloat_with_epsilon (value, expected, 1e-10);
        }
    }

  chl_matrix_free (m);
}

void
test_matrix_eq ()
{
  // basic test for identity matrices
  int       n  = 3;
  ChlMatrix a  = chl_matrix_eye (n);
  ChlMatrix b  = chl_matrix_eye (n);
  ChlMatrix c  = chl_matrix_eye (2);
  ChlMatrix z1 = chl_matrix_zeros (n, n);
  ChlMatrix z2 = chl_matrix_zeros (2, 2);

  g_assert_false (chl_matrix_eq (NULL, NULL));
  g_assert_true (chl_matrix_eq (a, a));
  g_assert_true (chl_matrix_eq (a, b));
  g_assert_true (chl_matrix_eq (b, a));
  g_assert_false (chl_matrix_eq (a, c));
  g_assert_false (chl_matrix_eq (a, z1));
  g_assert_false (chl_matrix_eq (a, z2));

  chl_matrix_free (a);
  chl_matrix_free (b);
  chl_matrix_free (c);
  chl_matrix_free (z1);
  chl_matrix_free (z2);
}

void
test_matrix_size ()
{
  int n_rows    = 3;
  int n_columns = 2;

  ChlMatrix m = chl_matrix_zeros (n_rows, n_columns);
  g_assert_cmpint (chl_matrix_rows (m), ==, n_rows);
  g_assert_cmpint (chl_matrix_cols (m), ==, n_columns);
  chl_matrix_free (m);
}

void
test_matrix_mult ()
{
  // square identity matrices
  ChlMatrix a = chl_matrix_eye (3);
  ChlMatrix b = chl_matrix_eye (3);

  ChlMatrix c = chl_matrix_mult (a, b);

  g_assert_true (chl_matrix_eq (a, c));

  chl_matrix_free (a);
  chl_matrix_free (b);
  chl_matrix_free (c);
}

int
main (int argc, char *argv[])
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/chl/matrix/new", test_matrix_new);
  g_test_add_func ("/chl/matrix/zeros", test_matrix_zeros);
  g_test_add_func ("/chl/matrix/eye", test_matrix_eye);
  g_test_add_func ("/chl/matrix/eq", test_matrix_eq);
  g_test_add_func ("/chl/matrix/size", test_matrix_size);
  g_test_add_func ("/chl/matrix/mult", test_matrix_mult);

  return g_test_run ();
}
