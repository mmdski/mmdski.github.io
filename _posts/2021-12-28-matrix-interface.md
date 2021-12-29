---
layout: post
title: Matrix Interface
tag: Build environment
date: 2021-12-28 23:21 -0600
---
I've started to implement a matrix object in C for this project. I'm using an [opaque pointer](https://en.wikipedia.org/wiki/Opaque_pointer)
for the structure implementation. I find that using opaque pointers for data types makes it easier for me to write more
complicated C code.

There are plenty of linear algebra libraries around, and I'm sure all of them are much faster than what I'll be able to
implement. I've heard that [GSL](https://www.gnu.org/software/gsl/){:target="_blank"}, which has a linear algebra
library, can be compiled to Wasm with Emscripten[^1], but I want to use this opportunity to learn about numerical linear
algebra. I plan on reading through Trefethen and Bau[^2] and implementing stuff I learn in this project.

In the past I've used [Meson](https://mesonbuild.com/){:target="_blank"} and
[Ninja](https://ninja-build.org/){:target="_blank"} for a build system, the
[GLib testing framework](https://docs.gtk.org/glib/testing.html){:target="_blank"} for unit tests, and
[Valgrind](https://valgrind.org/){:target="_blank"} for memory testing. I've worked with Meson and GLib on native
Windows with MSVC, but Valgrind isn't available on native Windows. I don't plan on making this project available on
Windows, so sticking with these tools will be fine for now. I'll have to write some instructions for myself to get a
build environment set up.

So far, I've implemented some basic matrix functionality in [the interface](https://github.com/mmdski/mmdski.github.io/blob/9403d62ed5a3c9d06b200fe3c337b8f030082c2f/chl/include/chl/chlmatrix.h){:target="_blank"}.
I plan on adding more as I start to read through _Numerical Linear Algebra_. After implementing and testing
functionality in a native build, I would like to demonstrate ideas in JavaScript/Wasm and show them in pages on this
site.

[^1]: [How to compile the C GNU Scientific Library (GSL) to web assembly using emscripten?](https://stackoverflow.com/questions/67159161/how-to-compile-the-c-gnu-scientific-library-gsl-to-web-assembly-using-emscript){:target="_blank"}.
[^2]: Trefethen, L. N., & Bau III, D. (1997). _Numerical linear algebra_. Society for Industrial and Applied Mathematics. [https://my.siam.org/Store/Product/viewproduct/?ProductId=950](https://my.siam.org/Store/Product/viewproduct/?ProductId=950){:target="_blank"}
