#include <emscripten.h>
#include <math.h>

EMSCRIPTEN_KEEPALIVE
void
mmdski_sinf_array(int size, float *t, float *x) {
  for (int i = 0; i < size; i++) {
    x[i] = sinf(t[i]);
  }
}

EMSCRIPTEN_KEEPALIVE
void
mmdski_sinf_func(
    int size, float *t, float *f, float amp, float freq, float phase) {

  for (int i = 0; i < size; i++) {
    f[i] = amp * sinf(freq * t[i] - phase);
  }
}
