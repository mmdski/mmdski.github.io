---
layout: post
title: Basic Matrix Operations
date: 2021-12-30 22:41 -0600
---
Since I've implemented some basic matrix operations in the C code base, I thought I would bring those operations to
the Wasm interface so I can use them in JavaScript. While I was doing that, I learned how to display the results of the
operations on a web page using MathJax. This will also give me an opportunity to test the functionality of the code
base. I have some unit and memory tests started in C, but I found myself writing a lot of test code instead of pushing
forward with learning about numerical linear algebra and implementing new functionality. I have the testing
infrastructure set up so I can quickly implement some tests if need be.

The operations below were all computed in your browser using the C code I wrote. The matrix interface in the code base
revolves around a matrix object, which is an opaque pointer as far as the JavaScript code is concerned. Matrix memory
management is initiated by the JavaScript code but handled by the C implementation. The JavaScript code calls functions
in Wasm to perform the operations and then formats the results as LaTeX after the operations are completed. MathJax
displays the LaTex as mathematical notation.

## Matrix multiplication

<!-- The product of the identity matrix $I$ and a vector $x$ -->

<p id="i-times-x-eq"></p>

<!-- Testing an output block:

<p id="output"></p> -->

<p id="a-times-x-eq"></p>

## Scalar multiplication

<!-- The product of a scalar $c=5$ and the identity matrix $I$ -->

<p id="c-times-i-eq"></p>

<p id="c-times-a-eq"></p>

## Linear combination

<!-- The linear combination of vectors $v$ and $w$ -->

<p id="linear-combo-eq"></p>

## Transpose

<!-- The transpose of $v$, $v^T$ -->

<p id="v-transpose-eq"></p>

<p id="a-transpose-eq"></p>

## Dot product

<!-- The dot product of vectors $v$ and $w$, $v^Tw$ -->

<p id="v-w-dot-eq"></p>

<script type="text/javascript">
    "use strict";

    var Module = {
        onRuntimeInitialized: function() {
            showDemo();
        }
    };

    function showDemo() {

        let outputLines = [];

        let n = 3;

        // define I
        let eye = _matrix_eye(n);

        let n_rows = _matrix_rows(eye);
        let n_cols = _matrix_cols(eye);
        outputLines.push("I has " + n_rows + " rows and " + n_cols + " columns");

        // define x
        let x = _matrix_new(n, 1);
        for (let i = 1; i <= n; i++) {
            _matrix_set(x, i, 1, 3+i)
        }

        // multiply I and x
        let x_product = _matrix_mult(eye, x);
        let xTimesIEq = document.getElementById("i-times-x-eq");
        xTimesIEq.textContent = "$$Ix = " + getMatrixTex(eye) + getMatrixTex(x) + " = " + getMatrixTex(x_product) + "$$";
        _matrix_free(x_product); // free the product

        // matrix multiplication: Ax
        let a = _matrix_new(2, 3);
        _matrix_set(a, 1, 1, -2);
        _matrix_set(a, 1, 2, 5);
        _matrix_set(a, 1, 3, 6);
        _matrix_set(a, 2, 1, 5);
        _matrix_set(a, 2, 2, 2);
        _matrix_set(a, 2, 3, 7);
        let aXProduct = _matrix_mult(a, x);
        let aTimesXEq = document.getElementById("a-times-x-eq");
        aTimesXEq.textContent = "$$Ax = " + getMatrixTex(a) + getMatrixTex(x) + " = " + getMatrixTex(aXProduct) + "$$";
        _matrix_free(x);
        _matrix_free(aXProduct);

        // scalar multiplication by I
        let c = 5;
        let cIProduct = _matrix_scalar_mult(c, eye);
        let cTimesIEq = document.getElementById("c-times-i-eq");
        cTimesIEq.textContent = "$$cI = " + c + getMatrixTex(eye) + " = " + getMatrixTex(cIProduct) + "$$"
        _matrix_free(cIProduct);
        _matrix_free(eye);

        // scalar multiplication by A
        let aIProduct = _matrix_scalar_mult(c, a);
        let aTimesIEq = document.getElementById("c-times-a-eq");
        aTimesIEq.textContent = "$$cA = " + c + getMatrixTex(a) + " = " + getMatrixTex(aIProduct) + "$$"
        _matrix_free(aIProduct);

        // linear combination of v and w
        let v = _matrix_new(2, 1);
        _matrix_set(v, 1, 1, 1);
        _matrix_set(v, 2, 1, 2);
        let w = _matrix_new(2, 1);
        _matrix_set(w, 1, 1, 3);
        _matrix_set(w, 2, 1, 4);
        let linearCombo = _matrix_add(v, w);
        let linearComboEq = document.getElementById("linear-combo-eq");
        linearComboEq.textContent = "$$v + w = " + getMatrixTex(v) + " + " + getMatrixTex(w) + " = " + getMatrixTex(linearCombo) + "$$";
        _matrix_free(linearCombo);

        // transpose v
        let vT = _matrix_transpose(v);
        let vTEq = document.getElementById("v-transpose-eq");
        vTEq.textContent = "$$v^T = " + getMatrixTex(vT) + "$$";

        // transpose a
        let aT = _matrix_transpose(a);
        let aTEq = document.getElementById("a-transpose-eq");
        aTEq.textContent = "$$A^T = " + getMatrixTex(aT) + "$$";
        _matrix_free(a);

        // dot product
        let vwDot = _matrix_dot(vT, w);
        let vwDotEq = document.getElementById("v-w-dot-eq");
        vwDotEq.textContent = "$$v^Tw = " + getMatrixTex(vT) + getMatrixTex(w) + " = " + vwDot + "$$";
        _matrix_free(vT);
        _matrix_free(v);
        _matrix_free(w);

        outputLines[0] = "<pre><code>" + outputLines[0];
        outputLines.push("</code></pre>");
        let outputParagraph = document.getElementById("output");
        <!-- outputParagraph.innerHTML = outputLines.join("\n"); -->

        MathJax.Hub.Queue(["Typeset", MathJax.Hub]);
    }

    function getMatrixTex(a) {

        let n_rows = _matrix_rows(a);
        let n_cols = _matrix_cols(a);

        let matrixTex = "\\begin{bmatrix}";
        for (let i = 1; i <= n_rows; i++) {
            matrixTex += " " + _matrix_get(a, i, 1);
            for (let j = 2; j <= n_cols; j++) {
                matrixTex += " & " + _matrix_get(a, i, j);
            }
            if (i < n_rows)
                matrixTex += " \\\\";
        }

        matrixTex += " \\end{bmatrix}";

        return matrixTex;
    }

    // console.log(eyePara.textContent);
</script>
<script type="text/javascript" src="{{ base.url | prepend: site.url }}/assets/js/chlib.js"></script>
