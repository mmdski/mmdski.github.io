/**
 * @file chlmatrix.h
 * @brief Matrix interface for CHL
 */

#ifndef __CHL_MATRIX_H__
#define __CHL_MATRIX_H__

#if !defined(__CHL_H_INSIDE__) && !defined(CHL_COMPILATION)
#error "Only <chl.h> can be included directly."
#endif

#include <chl/chlmath.h>
#include <stdbool.h>

/**
 * Matrix
 */
typedef struct ChlMatrix *ChlMatrix;

/**
 * @brief Creates a new uninitialized matrix
 *
 * @details Creates a new matrix with uninitialized values. This function
 * returns @c NULL if creation fails. The returned matrix must be freed with
 * chl_matrix_free() when no longer in use.
 *
 * @param n_rows number of rows
 * @param n_columns number of columns
 * @return new empty matrix
 */
extern ChlMatrix chl_matrix_new (int n_rows, int n_columns);

/**
 * @brief Creates a new matrix and initializes all entries to zero
 *
 * @details Creates a new matrix with all entries initialized to zero. This
 * function returns @c NULL if creation fails. The returned matrix must be freed
 * with chl_matrix_free() when no longer in use.
 *
 * @param n_rows number of rows
 * @param n_columns number of columns
 * @return new matrix
 */
extern ChlMatrix chl_matrix_zeros (int n_rows, int n_columns);

/**
 * @brief Creates a new square identity matrix
 *
 * @param n shape of square matrix
 * @return new identity matrix
 */
extern ChlMatrix chl_matrix_eye (int n);

/**
 * @brief Creates a new matrix in the same shape of another matrix
 *
 * @details The returned matrix must be freed with chl_matrix_free() when no
 * longer used.
 *
 * @param a a matrix
 * @return new matrix
 */
extern ChlMatrix chl_matrix_new_like (ChlMatrix a);

/**
 * @brief Frees a matrix
 *
 * @param a matrix to free
 * @return success indicator
 */
extern int chl_matrix_free (ChlMatrix a);

/**
 * @brief Gets an entry from a matrix
 *
 * @param a matrix
 * @param i row of entry
 * @param j column of entry
 * @param ptr pointer for value of entry
 * @return success indicator
 */
extern int chl_matrix_get (ChlMatrix a, int i, int j, real *ptr);

/**
 * @brief Sets an entry in a matrix
 *
 * @param a matrix
 * @param i row of entry
 * @param j column of entry
 * @param value value to set
 * @return success indicator
 */
extern int chl_matrix_set (ChlMatrix a, int i, int j, real value);

/**
 * @brief Returns the number of rows of a matrix
 *
 * @param a matrix
 * @return number of rows
 */
extern int chl_matrix_rows (ChlMatrix a);

/**
 * @brief Returns the number of columns of a matrix
 *
 * @param a matrix
 * @return number of columns
 */
extern int chl_matrix_cols (ChlMatrix a);

/**
 * @brief Returns @c true if @p a is equal to @p b, @c false otherwise.
 *
 * @param a a matrix
 * @param b another matrix
 * @return @c true if @p a is equal to @p b, @c false otherwise
 */
extern bool chl_matrix_eq (ChlMatrix a, ChlMatrix b);

/**
 * @brief Adds two matrices
 *
 * @details Adds two matrices of equal shape. The returned matrix must be freed
 * with chl_matrix_free() when no longer used.
 *
 * @param a a matrix
 * @param b another matrix
 * @returns sum of matrices @p a and @p b
 */
extern ChlMatrix chl_matrix_add (ChlMatrix a, ChlMatrix b);
/**
 * @brief Multiplies two matrices
 *
 * @details Multiplies two matrices @p a and @p b and returns the product matrix
 * to. The inner dimensions of @p a and @p b must be equal. The returned matrix
 * must be freed with chl_matrix_free() when no longer used.
 *
 * @param a left matrix
 * @param b right matrix
 * @return success indicator
 */
extern ChlMatrix chl_matrix_mult (ChlMatrix a, ChlMatrix b);

/**
 * @brief Multiplies a matrix by a scalar
 *
 * @details Multiplies a matrix @p m by a scalar @p c and returns the resulting
 * matrix. The returned matrix must be freed with chl_matrix_free() when no
 * longer used.
 *
 * @param a a matrix
 * @param c a scalar
 * @return result of scalar multiplication
 */
extern ChlMatrix chl_matrix_scalar_mult (ChlMatrix a, real c);

/**
 * @brief Returns the transpose of a matrix
 *
 * @details Returns the transpose of matrix @p a. The returned matrix is newly
 * created and must be freed with chl_matrix_free() when no longer in use.
 *
 * @param a matrix
 * @return transpose of @p a
 */
extern ChlMatrix chl_matrix_transpose (ChlMatrix a);

#endif
