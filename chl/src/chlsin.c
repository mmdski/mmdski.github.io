#include <emscripten.h>
#include <math.h>
#include <stdio.h>

#define REAL float

EMSCRIPTEN_KEEPALIVE
REAL
chl_sin (REAL x)
{
  return sinf (x);
}

EMSCRIPTEN_KEEPALIVE
void
chl_sin_array (int size, REAL *t, REAL *x)
{
  for (int i = 0; i < size; i++)
    {
      x[i] = sinf (t[i]);
    }
}
