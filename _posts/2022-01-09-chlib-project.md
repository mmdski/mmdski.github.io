---
layout: post
title: chlib Project
date: 2022-01-09 19:42 -0600
---
chlib is the small library that I began to implement some matrix functionality in. The functionality was demonstrated in
[a previous post]({% post_url 2021-12-30-basic-matrix-operations %}). The code and build files were previously hosted in
this project repository.

## Purpose

The purpose of the chlib project is to be a C library to provide a functionality for... something to be discussed later.
I have a vague goal in mind, but I don't want to reveal what it is until the project takes shape and it seems that the
codebase is approaching that goal. In an earlier post I mentioned a book on numerical linear algebra that I was going to
follow along with, but I've changed my mind. I'd like to start implementing things that I learn while I follow
MIT's OCW
[18.085](https://ocw.mit.edu/courses/mathematics/18-085-computational-science-and-engineering-i-fall-2008/){:target="_blank"}.
I've followed along with a few other OCW courses before, and it really helps to have lecture videos to watch along with
homework and solutions to the homework. I plan on following OCW 18.085 on with OCW
[18.086](https://ocw.mit.edu/courses/mathematics/18-086-mathematical-methods-for-engineers-ii-spring-2006/){:target="_blank"}.
Both of the courses seem pretty interesting and I'm hoping they will give me some groundwork to build from to more
towards the *actual* goal of chlib.

## New Project Repository

I've removed the chlib project from the repo that hosts the files for this site since I thought it would be cumbersome
to deal with all of the different things happening here. chlib is now hosted in another
[GitHub repository](https://github.com/mmdski/chlib){:target="_blank"}. I've also created a
[project home page](https://mmdski.github.io/chlib){:target="_blank"} for chlib. I'll be including some JavaScript
demonstrations, such as the [basic matrix demo](https://mmdski.github.io/chlib/demo/matrix.html){:target="_blank"}, in
the chlib project documentation site. I'd like to continue to include some static demonstrations on this site, but I
think it will be more manageable for me if I have one place that hosts JavaScript code that I can change as the API
changes. That being said, I'd like to figure out a way to host multiple versions of the JavaScript/Wasm chlib code on
this site so all of my posts don't just break when I have to make a change to the JavaScript API. Since I'm just
beginning to develop chlib, I'd like to avoid giving a version number to the library, but one option may be to create a
new directory for each version of the API.

## Changes

I started working on macOS a few days ago. I was working on a Linux machine before so everything in the project was set
up to run on an x86 Linux platform. I've decided to use the opportunity to make some changes to the project to make
testing more portable.

I've removed the dependency on GLib for software testing. GLib is available through Homebrew on macOS, but I wanted to
try and keep testing simpler. The tests are now simple executable files and Meson pretty much handles the tests now.
I've just added some assertion macros that build the macro in `stdlib.h`.
I've considered using [Google Test](https://github.com/google/googletest){:target="_blank"} and I may switch if using
simple executables becomes too difficult as the project grows. An advantage of using simple executables is that I can
easily combine the software tests with the memory tests. I've done this before with GLib and Valgrind, but I had to set
some options with Valgrind and the tests took a while to run if I remember correctly.

Since chlib depended on Valgrind for memory tests, and Valgrind isn't able to run on Apple silicon just yet, I had to
make a change to the way memory tests were conducted. I've switched the memory testing to use
[ASan](https://clang.llvm.org/docs/AddressSanitizer.html){:target="_blank"} and
[LSan](https://clang.llvm.org/docs/LeakSanitizer.html){:target="_blank"}. They're both a part of GCC and Clang, and I've
tested them both on macOS and Fedora 35. The catch on macOS is that LSan is not available with the system LLVM, so Is
have to use a Homebrew installed version. It's not that big of a deal but it does require some setting up. I set up a
[simple project](https://github.com/mmdski/memleak){:target="_blank"} that uses the Meson build system to build a
project. Testing the project should fail (see output below).

```
% ninja -C build test
ninja: Entering directory `build'
[2/3] Running all tests.
1/1 testmem        FAIL            0.80s   exit status 1
>>> ASAN_OPTIONS=detect_leaks=1 MALLOC_PERTURB_=137 /Users/marian/src/memleak/build/memleak_test
――――――――――――――――――――――――――――――――――――― ✀  ―――――――――――――――――――――――――――――――――――――
stderr:

=================================================================
==9844==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 7 byte(s) in 1 object(s) allocated from:
    #0 0x10273b6d8 in wrap_malloc+0x8c (libclang_rt.asan_osx_dynamic.dylib:arm64+0x3f6d8)
    #1 0x1022cfee0 in main memory-leak.c:5
    #2 0x1024510f0 in start+0x204 (dyld:arm64+0x50f0)
    #3 0x4f657ffffffffffc  (<unknown module>)

SUMMARY: AddressSanitizer: 7 byte(s) leaked in 1 allocation(s).
――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――


Summary of Failures:

1/1 testmem FAIL            0.80s   exit status 1


Ok:                 0
Expected Fail:      0
Fail:               1
Unexpected Pass:    0
Skipped:            0
Timeout:            0

Full log written to /Users/marian/src/memleak/build/meson-logs/testlog.txt
FAILED: meson-test
/opt/homebrew/bin/meson test --no-rebuild --print-errorlogs
ninja: build stopped: subcommand failed.
```

### The Future of chlib

Well, chlib hardly has a present, so it's difficult what will happen in the future. As I said before, I want to follow
along with some OCW courses from MIT and implement some base-level numerical methods for now. After that, I'd like to
start working towards some application specific functionality. The applications will be extremely simplified and
abstract, but I'd like to use chlib to demonstrate these application specific concepts in both JavaScript and in Python.
I want chlib to be a library written in C that contains core functionality. The C code will be able to be extended in
JavaScript by compiling it to Wasm, and in Python by using either [Cython](https://cython.org){:target="_blank"} or
[ctypes](https://docs.python.org/3/library/ctypes.html){:target="_blank"}.
