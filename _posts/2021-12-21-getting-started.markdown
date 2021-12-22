---
layout: post
title:  "Getting started with web assembly"
date:   2021-12-21 18:55:29 -0600
categories: [wasm, JavaScript]
---

The values in the plot below are computed with a sine function called from JavaScript and written in C code. The C code
was compiled to web assembly using [Emscripten](https://emscripten.org/). The plot itself is created in
[Plotly](https://plotly.com/javascript/). Web assembly and JavaScript are very new to me and I still have a lot of
learning to do. I'm planning on learning more on how to make this plot a bit more interactive, and I'd like to add an
animation feature.

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
