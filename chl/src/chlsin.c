#include <chl.h>
#include <emscripten.h>
#include <math.h>

EMSCRIPTEN_KEEPALIVE
REAL
chl_sin (REAL x)
{
  return sinf (x);
}

EMSCRIPTEN_KEEPALIVE
REAL *
chl_pi ()
{
  REAL pi = 3.14;
  return &pi;
}
