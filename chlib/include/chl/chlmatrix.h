/**
 * @file chlmatrix.h
 * @brief Matrix interface
 */

#ifndef __CHL_MATRIX_H__
#define __CHL_MATRIX_H__

#if !defined(__CHL_H_INSIDE__) && !defined(CHL_COMPILATION)
#error "Only <chl.h> can be included directly."
#endif

#include <chl/chlmath.h>
#include <stdbool.h>

/**
 * Matrix object
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
 * @brief Creates a new matrix from allocated memory
 *
 * @details Creates a new matrix from allocated memory. This function
 * returns @c NULL if creation fails. The returned matrix must be freed with
 * chl_matrix_free() when no longer in use. chl_matrix_free() will not free the
 * memory allocated for @p entries.
 *
 * @param n_rows number of rows
 * @param n_columns number of columns
 * @param entries pointer to allocated memory for matrix entries
 * @return new empty matrix
 */
extern ChlMatrix chl_matrix_new_from (int n_rows, int n_columns, real *entries);

/**
 * @brief Creates a new matrix and initializes all entries to zero
 *
 * @details Creates a new matrix with all entries initialized to zero. This
 * function returns @c NULL if creation fails. The returned matrix must be freed
 * with chl_matrix_free() when no longer in use.
 *
 * @param n_rows number of rows
 * @param n_columns number of columns
 * @return a new matrix
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
 * @returns 0 if operation was a success, -1 otherwise
 */
extern int chl_matrix_free (ChlMatrix a);

/**
 * @brief Gets an entry from a matrix
 *
 * @param a matrix
 * @param i row of entry
 * @param j column of entry
 * @param ptr pointer for value of entry
 * @returns 0 if operation was a success, -1 otherwise
 */
extern int chl_matrix_get (ChlMatrix a, int i, int j, real *ptr);

/**
 * @brief Sets an entry in a matrix
 *
 * @param a matrix
 * @param i row of entry
 * @param j column of entry
 * @param value value to set
 * @returns 0 if operation was a success, -1 otherwise
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
 * @details Adds two matrices of equal shape and sets the result to the matrix
 * @p c. The dimensions of @p a and @p b must be equal.
 *
 * @p c may be @c NULL. If @p c is @c NULL, a new matrix will be created. This
 * newly created matrix must be freed with chl_matrix_free() when no longer in
 * use.
 *
 * If @p c is not @c NULL, @p c must have the same dimensions of @p a and @p b.
 *
 * @param a a matrix
 * @param b another matrix
 * @param c pointer to sum of @p a and @p b
 * @returns 0 if operation was a success, -1 otherwise
 */
extern int chl_matrix_add (ChlMatrix a, ChlMatrix b, ChlMatrix *c_ptr);

/**
 * @brief Multiplies two matrices
 *
 * @details Multiplies two matrices @p a and @p b and sets the result to the
 * matrix @p c. The inner dimensions of @p a and @p b must be equal.
 *
 * @p c may be @c NULL. If @p c is @c NULL, a new matrix will be created. This
 * newly created matrix must be freed with chl_matrix_free() when no longer in
 * use.
 *
 * If @p c is not @c NULL, @p c must have dimensions equal to the outer
 * dimensions of @p a and @p b.
 *
 * @param a left matrix
 * @param b right matrix
 * @param c_ptr pointer to product of @p a and @p b
 * @returns 0 if operation was a success, -1 otherwise
 */
extern int chl_matrix_mult (ChlMatrix a, ChlMatrix b, ChlMatrix *c_ptr);

/**
 * @brief Multiplies a matrix by a scalar
 *
 * @details Multiplies a matrix @p a by a scalar @p c.
 *
 * @param a a matrix
 * @param c a scalar
 * @param b_ptr pointer to product of @p c and @p a
 * @return 0 if operation was a success, -1 otherwise
 */
extern int chl_matrix_scalar_mult (ChlMatrix a, real c, ChlMatrix *b_ptr);

/**
 * @brief Returns the dot product of two vectors
 *
 * @details Returns the dot (scalar) product of two vectors. The outer
 * dimensions of @p a and @p b must be 1, and the inner dimensions must be
 * equal.
 *
 * @param a a row vector
 * @param b a column vector
 * @param dot a pointer to a real value
 * @return 0 if operation was a success, -1 otherwise
 */
extern int chl_matrix_dot (ChlMatrix a, ChlMatrix b, real *dot);

/**
 * @brief Returns the transpose of a matrix
 *
 * @param a matrix
 * @param a_t_ptr pointer to transpose of @p a
 * @return 0 if operation was a success, -1 otherwise
 */
extern int chl_matrix_transpose (ChlMatrix a, ChlMatrix *a_t_ptr);

#endif
