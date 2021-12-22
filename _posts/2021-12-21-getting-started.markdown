---
layout: post
title:  "Getting started with WebAssembly"
date:   2021-12-21 18:55:29 -0600
tags: [Wasm, JavaScript]
---

I've decided to learn how to write static web applications. I don't think there is a better way to deliver applications
to people than through the web. Obviously I'm pretty late on coming to this conclusion. Instead of making someone
download and install a runtime or development environment, you can give someone a URL and they can seamlessly download
and run your code, assuming the application is in working order.

Since I would like to eventually write computationally intense applications, I want to learn how to use
[WebAssembly (Wasm)](https://webassembly.org/) right away. I don't think a lot of the smaller applications I initially
write will benefit from using Wasm (actually they'll probably suffer from it) but I would like to get the hang of it
before I really need to use it. I'm also learning JavaScript, which I loath at this point, so coding in C will be a much
more pleasant experience for me.

The values in the plot below are computed with a standard library sine function in C code called from JavaScript. The C
code was compiled to Wasm using [Emscripten](https://emscripten.org/). The plot itself is created in
[Plotly](https://plotly.com/javascript/).

<div id="tester" style="width:600px;height:500px;"></div>

<script type="text/javascript">

    var Module = {
        onRuntimeInitialized: function() {
            plotsin();
        }
    };

    function plotsin() {
        "use strict";

        let size = 1000;

        // allocate memory for t and create a buffer from the heap
        let t_ptr = _calloc(size, Float32Array.BYTES_PER_ELEMENT);
        let t = new Float32Array(HEAPF32.buffer, t_ptr, size);

        let max = 2 * Math.PI;

        for (let i = 0; i <= size; i++) {
            t[i] = i / size * max;
        }

        // allocate memory for x
        let x_ptr = _calloc(size, Float32Array.BYTES_PER_ELEMENT);

        // compute the sin of t and store it in x
        _chl_sin_array(size, t_ptr, x_ptr);

        // create a buffer from x on the heap
        let x = new Float32Array(HEAPF32.buffer, x_ptr, size);

        // plot sin(t)
        let TESTER = document.getElementById('tester');
        let trace = { x: t, y: x, type: 'line' };
        let layout = {};
        let config = { staticPlot: true };
        Plotly.newPlot(TESTER, [trace], layout, config);

        // free the t and x memory
        _free(t_ptr);
        _free(x_ptr);
    }

</script>
<script type="text/javascript" src="https://cdn.plot.ly/plotly-2.6.3.min.js"></script>
<script type="text/javascript" src="{{ base.url | prepend: site.url }}/assets/js/chlsin.js"></script>
