"use strict";

/** Wrapper class for chlib matrix implementation */
class Matrix {

    /**
     * Create a matrix
     * @param {number} n_rows - Number of rows in the matrix
     * @param {number} n_columns - Number of columns in the matrix
     * @param {number} entries_ptr - Pointer to allocated matrix memory
     */
    constructor(n_rows, n_columns, entries_ptr) {
        this.n_rows = n_rows;
        this.n_columns = n_columns;
        this._matrix = _matrix_new_from(n_rows, n_columns, entries_ptr);
        this._free_entries = false;

        let ptr_offset;
        this._rows = {};
        for (let i = 0; i < n_rows; i++) {
            ptr_offset = i * n_columns * Float32Array.BYTES_PER_ELEMENT;
            this._rows[i] = new Float32Array(HEAPF32.buffer, entries_ptr + ptr_offset, n_columns);
        }
    }

    /**
     * Allocates memory for a n_rows by n_columns matrix and returns a pointer
     * @param {number} n_rows - Number of rows
     * @param {number} n_columns - Number of columns
     * @returns {number}
     */
    static _alloc(n_rows, n_columns) {
        return _calloc(n_rows * n_columns, Float32Array.BYTES_PER_ELEMENT);
    }

    /**
     * Returns the sum of this and another matrix.
     * @param {Matrix} other - Another matrix
     * @returns {Matrix} Sum of this matrix and other
     */
    add(other) {
        let sum = Matrix.new(this.n_rows, this.n_columns);
        _matrix_add(this._matrix, other._matrix, sum._matrix);
        return sum;
    }

    /**
     * Returns an n by n identity matrix.
     * @param {number} n - Number of rows and columns in the identity matrix
     * @returns {Matrix} Identity matrix
     */
    static eye(n) {
        let eye = Matrix.new(n, n);
        let entry;
        for (let i = 1; i <= n; i++) {
            for (let j = 1; j <= n; j++) {
                if (i == j)
                    entry = 1;
                else
                    entry = 0;
                eye.set(i, j, entry);
            }
        }

        return eye;
    }

    /**
     * Frees the resources contained in a matrix.
     *
     * Must be called when this matrix is no longer in use.
     */
    free() {
        _matrix_free(this._matrix);
        delete this._matrix;
        if (this._free_entries) {
            _free(this._entries);
            delete this._entries;
        }
    }

    get(row, col) {
        return this._rows[row - 1][col - 1];
    }

    /**
     * Returns the product of this matrix and other.
     *
     * If this is a row vector and other is a column vector, the operation is
     * a dot product and a scalar is returned.
     *
     * @param {(number | Matrix)} other - Scalar or another matrix
     * @returns {(number | Matrix)} Product
     */
    multiply(other) {

        let product;

        if (typeof (other) === 'number') {
            product = Matrix.new(this.n_rows, this.n_columns);
            _matrix_scalar_mult(this._matrix, other, product._matrix);
        }
        else if (Object.getPrototypeOf(this) === Object.getPrototypeOf(other)) {
            if (this.n_rows === 1 && other.n_columns === 1) {
                product = _matrix_dot(this._matrix, other._matrix);
            } else {
                product = Matrix.new(this.n_rows, other.n_columns);
                _matrix_mult(this._matrix, other._matrix, product._matrix);
            }
        }

        return product;
    }

    /**
     * Returns a new matrix.
     * @param {number} n_rows - Number of rows in the matrix
     * @param {number} n_columns - Number of columns in the matrix
     * @returns {Matrix} A new matrix
     */
    static new(n_rows, n_columns) {
        // allocate memory for the matrix elements
        let entries_ptr = Matrix._alloc(n_rows, n_columns);
        let matrix = new Matrix(n_rows, n_columns, entries_ptr);
        matrix._free_entries = true;
        return matrix;
    }

    set(row, col, value) {
        this._rows[row - 1][col - 1] = value;
    }

    /**
     * Returns a TeX string representation of this matrix.
     * @returns {String} TeX representation of this matrix.
     */
    toTex() {

        let matrixTex = "\\begin{bmatrix}";
        for (let i = 1; i <= this.n_rows; i++) {
            matrixTex += " " + _matrix_get(this._matrix, i, 1);
            for (let j = 2; j <= this.n_columns; j++) {
                matrixTex += " & " + _matrix_get(this._matrix, i, j);
            }
            if (i < this.n_rows)
                matrixTex += " \\\\";
        }

        matrixTex += " \\end{bmatrix}";

        return matrixTex;
    }

    /**
     * Returns the transpose of this matrix.
     * @returns {Matrix} The transpose of this matrix.
     */
    transpose() {
        let transpose = Matrix.new(this.n_columns, this.n_rows);
        _matrix_transpose(this._matrix, transpose._matrix);
        return transpose;
    }
}
