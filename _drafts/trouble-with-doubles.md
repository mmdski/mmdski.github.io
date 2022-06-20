---
layout: post
title: Trouble with Doubles
---

```c
#include <math.h>

/**
 * @brief Rounds a double to a specified base-10 precision
 *
 * @param value value to convert
 * @param precision number of base-10 digits of return value
 * @return double
 */
double fl(double value, unsigned int precision)
{

  // base-10 exponent
  double exp10;

  // -infinity or +infinity, depending on the sign of value
  double inf;

  if (value > 0)
  {
    exp10 = ceil(log10(value));
    inf = INFINITY;
  }
  else if (value < 0)
  {
    exp10 = ceil(log10(-value)); // logarithm of abs(value)
    inf = -INFINITY;
  }

  // return 0 if value is 0
  else
  {
    return value;
  }

  // true normalized form of significand
  double sig10 = value / pow(10, exp10);

  // value to round
  // multiply by 10**precision to move the significant digits of the result to
  //   the integral position
  // use nextafter to get the fp value with the next-largest magnitude. this
  // helps round values up when necessary
  double to_round = nextafter(sig10 * pow(10, precision), inf);

  // round to integral value
  double rounded = round(to_round);

  // apply exponent and divide by 10**precision to get fractional value
  double fl = pow(10, exp10) * rounded / pow(10, precision);

  return fl;
}
```
