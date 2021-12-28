#include "chlmem.h"
#include <chl/chlmatrix.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

struct ChlMatrix
{
  int    n_rows;    /* number of rows */
  int    n_columns; /* number of columns */
  real **columns;   /* column arrays */
};

ChlMatrix
chl_matrix_new (int n_rows, int n_columns)
{
  if (n_rows <= 0 || n_columns <= 0)
    {
      return NULL;
    }

  ChlMatrix m;
  NEW (m);

  if (m == 0)
    abort ();

  m->n_rows    = n_rows;
  m->n_columns = n_columns;

  real **columns = chl_calloc (n_columns, sizeof (real *));
  for (int i = 0; i < n_columns; i++)
    {
      *(columns + i) = chl_calloc (n_rows, sizeof (real *));
    }

  m->columns = columns;

  return m;
}

int
chl_matrix_free (ChlMatrix m)
{

  if (m == NULL)
    return -1;

  int    n_columns = m->n_columns;
  real **columns   = m->columns;
  for (int i = 0; i < n_columns; i++)
    {
      chl_free (*(columns + i));
    }

  chl_free (columns);

  FREE (m);

  return 0;
}

ChlMatrix
chl_matrix_zeros (int n_rows, int n_columns)
{

  if (n_rows <= 0 || n_columns <= 0)
    return NULL;

  ChlMatrix m = chl_matrix_new (n_rows, n_columns);
  if (m == NULL)
    return NULL;

  for (int i = 1; i <= n_rows; i++)
    {
      for (int j = 1; j <= n_columns; j++)
        {
          chl_matrix_set (m, i, j, 0);
        }
    }

  return m;
}

ChlMatrix
chl_matrix_eye (int n)
{

  if (n <= 0)
    return NULL;

  ChlMatrix m = chl_matrix_new (n, n);

  for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= n; j++)
        {
          if (i == j)
            chl_matrix_set (m, i, j, 1);
          else
            chl_matrix_set (m, i, j, 0);
        }
    }

  return m;
}

int
chl_matrix_rows (ChlMatrix m)
{
  if (m == NULL)
    return -1;
  return m->n_rows;
}

int
chl_matrix_cols (ChlMatrix m)
{
  if (m == NULL)
    return -1;

  return m->n_columns;
}

bool
chl_matrix_eq (ChlMatrix a, ChlMatrix b)
{
  if (a == NULL || b == NULL)
    {
      return false;
    }

  if (a == b)
    {
      return true;
    }

  if (chl_matrix_rows (a) != chl_matrix_rows (b))
    {
      return false;
    }

  if (chl_matrix_cols (a) != chl_matrix_cols (b))
    {
      return false;
    }

  int n_rows = chl_matrix_rows (a);
  int n_cols = chl_matrix_cols (a);

  real a_value;
  real b_value;

  for (int i = 1; i <= n_rows; i++)
    {
      for (int j = 1; j < n_cols; j++)
        {
          chl_matrix_get (a, i, j, &a_value);
          chl_matrix_get (b, i, j, &b_value);
          if (a_value != b_value)
            {
              return false;
            }
        }
    }

  return true;
}

int
chl_matrix_get (ChlMatrix m, int i, int j, real *value)
{
  // check for null pointer
  if (m == NULL)
    return -1;

  // check for valid indices
  if (i < 1 || i > m->n_rows || j < 1 || j > m->n_columns)
    return -1;

  real *column = *(m->columns + j - 1);
  *value       = *(column + i - 1);

  return 0;
}

int
chl_matrix_set (ChlMatrix m, int i, int j, real value)
{

  // check for null pointer
  if (m == NULL)
    return -1;

  // check for valid indices
  if (i < 1 || i > m->n_rows || j < 1 || j > m->n_columns)
    return -1;

  real *column      = *(m->columns + j - 1);
  *(column + i - 1) = value;

  return 0;
}

ChlMatrix
chl_matrix_mult (ChlMatrix a, ChlMatrix b)
{
  // check for null pointers
  if (a == NULL || b == NULL)
    {
      return NULL;
    }

  // check inner dimensions
  if (a->n_columns != b->n_rows)
    {
      return NULL;
    }

  // initialize the new matrix
  int       n_rows    = a->n_rows;
  int       n_columns = b->n_columns;
  ChlMatrix c         = chl_matrix_new (n_rows, n_columns);

  real a_value;
  real b_value;
  real c_value;

  int inner_dim = a->n_columns;

  for (int i = 1; i <= n_rows; i++)
    {
      for (int j = 1; j <= n_columns; j++)
        {
          c_value = 0;
          for (int k = 1; k <= inner_dim; k++)
            {
              chl_matrix_get (a, i, k, &a_value);
              chl_matrix_get (b, k, j, &b_value);
              c_value += a_value * b_value;
            }
          chl_matrix_set (c, i, j, c_value);
        }
    }

  return c;
}
