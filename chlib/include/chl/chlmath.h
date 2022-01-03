/**
 * @file chlmath.h
 * @brief Math definitions
 */

#ifndef __CHL_MATH_H__
#define __CHL_MATH_H__

#if !defined(__CHL_H_INSIDE__) && !defined(CHL_COMPILATION)
#error "Only <chl.h> can be included directly."
#endif

#if defined(REAL_IS_FLOAT)
typedef float real;
#else
/**
 * @brief Real number type used throughout chlib
 *
 */
typedef double real;
#endif

#endif
