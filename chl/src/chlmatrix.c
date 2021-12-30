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

// creates a new n_rows by n_columns matrix and leaves entries uninitialized
ChlMatrix
chl_matrix_new (int n_rows, int n_columns)
{
  if (n_rows <= 0 || n_columns <= 0)
    {
      return NULL;
    }

  ChlMatrix a;
  NEW (a);

  if (a == 0)
    abort ();

  a->n_rows    = n_rows;
  a->n_columns = n_columns;

  real **columns = (real **) chl_calloc (n_columns, sizeof (real **));
  for (int i = 0; i < n_columns; i++)
    {
      *(columns + i) = (real *) chl_calloc (n_rows, sizeof (real *));
    }

  a->columns = columns;

  return a;
}

// creates a new n_rows by n_columns matrix and fills entries with zeros
ChlMatrix
chl_matrix_zeros (int n_rows, int n_columns)
{

  if (n_rows <= 0 || n_columns <= 0)
    return NULL;

  ChlMatrix a = chl_matrix_new (n_rows, n_columns);
  if (a == NULL)
    return NULL;

  for (int i = 1; i <= n_rows; i++)
    {
      for (int j = 1; j <= n_columns; j++)
        {
          if (chl_matrix_set (a, i, j, 0) < 0)
            goto fail;
        }
    }

  return a;

fail:
  chl_matrix_free (a);
  return NULL;
}

// creates a new n by n identity matrix
ChlMatrix
chl_matrix_eye (int n)
{

  if (n <= 0)
    return NULL;

  ChlMatrix a = chl_matrix_new (n, n);

  for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= n; j++)
        {
          if (i == j)
            {
              if (chl_matrix_set (a, i, j, 1) < 0)
                goto fail;
            }
          else
            {
              if (chl_matrix_set (a, i, j, 0) < 0)
                goto fail;
            }
        }
    }

  return a;

fail:
  chl_matrix_free (a);
  return NULL;
}

// creates a new uninitialized matrix in the same shape as m
ChlMatrix
chl_matrix_new_like (ChlMatrix a)
{

  if (a == NULL)
    return NULL;

  return chl_matrix_new (a->n_rows, a->n_columns);
}

// frees a matrix
int
chl_matrix_free (ChlMatrix a)
{

  if (a == NULL)
    return -1;

  int    n_columns = a->n_columns;
  real **columns   = a->columns;
  for (int i = 0; i < n_columns; i++)
    {
      chl_free (*(columns + i));
    }

  chl_free (columns);

  FREE (a);

  return 0;
}

// returns the number of rows in m
int
chl_matrix_rows (ChlMatrix a)
{
  if (a == NULL)
    return -1;

  return a->n_rows;
}

// returns the number of columns in m
int
chl_matrix_cols (ChlMatrix a)
{
  if (a == NULL)
    return -1;

  return a->n_columns;
}

// returns true if all entries in a and b are exactly equal
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

// gets an entry from a matrix (1-indexed)
int
chl_matrix_get (ChlMatrix a, int i, int j, real *value)
{
  // check for null pointer
  if (a == NULL)
    return -1;

  // check for valid indices
  if (i < 1 || i > a->n_rows || j < 1 || j > a->n_columns)
    return -1;

  real *column = *(a->columns + (j - 1));
  *value       = *(column + (i - 1));

  return 0;
}

// sets an entry in a matrix (1-indexed)
int
chl_matrix_set (ChlMatrix a, int i, int j, real value)
{

  // check for null pointer
  if (a == NULL)
    return -1;

  // check for valid indices
  if (i < 1 || i > a->n_rows || j < 1 || j > a->n_columns)
    return -1;

  real *column        = *(a->columns + (j - 1));
  *(column + (i - 1)) = value;

  return 0;
}

// adds matrices
int
chl_matrix_add (ChlMatrix a, ChlMatrix b, ChlMatrix *c_ptr)
{
  // check for null pointers
  if (a == NULL || b == NULL)
    {
      return -1;
    }

  // check for equal dimensions
  if (a->n_rows != b->n_rows || a->n_columns != b->n_columns)
    {
      return -1;
    }

  int n_rows    = a->n_rows;
  int n_columns = a->n_columns;

  ChlMatrix c      = *c_ptr;
  bool      free_c = false;

  if (c == NULL)
    {
      free_c = true;
      c      = chl_matrix_new (n_rows, n_columns);
      *c_ptr = c;
    }
  else
    {
      c = *c_ptr;
      if (c->n_rows != n_rows || c->n_columns != n_columns)
        goto fail;
    }

  real a_value;
  real b_value;

  for (int i = 1; i <= n_rows; i++)
    {
      for (int j = 1; j <= n_columns; j++)
        {
          if (chl_matrix_get (a, i, j, &a_value) < 0)
            goto fail;
          if (chl_matrix_get (b, i, j, &b_value) < 0)
            goto fail;
          if (chl_matrix_set (c, i, j, a_value + b_value) < 0)
            goto fail;
        }
    }

  return 0;

fail:
  if (free_c)
    {
      chl_matrix_free (c);
      c = NULL;
    }
  return -1;
}

// multiplies matrices
int
chl_matrix_mult (ChlMatrix a, ChlMatrix b, ChlMatrix *c_ptr)
{
  // check for null pointers
  if (a == NULL || b == NULL)
    {
      return -1;
    }

  // check inner dimensions
  if (a->n_columns != b->n_rows)
    {
      return -1;
    }

  // initialize the new matrix
  int n_rows    = a->n_rows;
  int n_columns = b->n_columns;

  ChlMatrix c      = *c_ptr;
  bool      free_c = false;

  if (c == NULL)
    {
      free_c = true;
      c      = chl_matrix_new (n_rows, n_columns);
      *c_ptr = c;
    }
  else
    {
      c = *c_ptr;
      if (c->n_rows != n_rows || c->n_columns != n_columns)
        goto fail;
    }

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
              if (chl_matrix_get (a, i, k, &a_value) < 0)
                goto fail;
              if (chl_matrix_get (b, k, j, &b_value) < 0)
                goto fail;
              c_value += a_value * b_value;
            }
          if (chl_matrix_set (c, i, j, c_value) < 0)
            goto fail;
        }
    }

  return 0;

fail:
  if (free_c)
    {
      chl_matrix_free (c);
      c = NULL;
    }
  return -1;
}

// matrix scalar multiplication
int
chl_matrix_scalar_mult (real c, ChlMatrix a, ChlMatrix *b_ptr)
{

  if (a == NULL)
    return -1;

  int n_rows    = a->n_rows;
  int n_columns = a->n_columns;

  ChlMatrix b      = *b_ptr;
  bool      free_b = false;

  if (b == NULL)
    {
      free_b = true;
      b      = chl_matrix_new (n_rows, n_columns);
      *b_ptr = b;
    }
  else
    {
      b = *b_ptr;
      if (b->n_rows != n_rows || b->n_columns != n_columns)
        goto fail;
    }

  real value;

  for (int i = 1; i <= n_rows; i++)
    {
      for (int j = 1; j <= n_columns; j++)
        {
          if (chl_matrix_get (a, i, j, &value) < 0)
            goto fail;

          if (chl_matrix_set (b, i, j, c * value) < 0)
            goto fail;
        }
    }

  return 0;

fail:
  if (free_b)
    {
      chl_matrix_free (b);
      b = NULL;
    }
  return -1;
}

// matrix transpose
int
chl_matrix_transpose (ChlMatrix a, ChlMatrix *a_t_ptr)
{

  if (a == NULL)
    return -1;

  int n_rows    = a->n_columns;
  int n_columns = a->n_rows;

  ChlMatrix a_t      = *a_t_ptr;
  bool      free_a_t = false;

  if (a_t == NULL)
    {
      free_a_t = true;
      a_t      = chl_matrix_new (n_rows, n_columns);
      *a_t_ptr = a_t;
    }
  else
    {
      a_t = *a_t_ptr;
      if (a_t->n_rows != n_rows || a_t->n_columns != n_columns)
        goto fail;
    }

  real value;

  for (int i = 1; i <= n_rows; i++)
    {
      for (int j = 1; j <= n_columns; j++)
        {
          if (chl_matrix_get (a, j, i, &value) < 0)
            goto fail;
          if (chl_matrix_set (a_t, i, j, value) < 0)
            goto fail;
        }
    }

  return 0;

fail:
  if (free_a_t)
    {
      chl_matrix_free (a_t);
      a_t = NULL;
    }
  return -1;
}
