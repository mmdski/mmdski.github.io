#include <emscripten.h>
#include <math.h>

EMSCRIPTEN_KEEPALIVE
double
chl_sin (double x)
{
  return sin (x);
}
