---
layout: post
title: Interactive Sine Wave
tags: [Wasm, JavaScript]
---
Generally, a [sine wave](https://en.wikipedia.org/wiki/Sine_wave) as a function of time is

$$ f\left(t\right) = A\sin\left(\omega t + \phi\right) $$

where $A$ is the amplitude, $\omega$ is the angular frequency, and $\phi$ is the phase of the wave.

<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
.slidecontainer {
  width: 100%;
}

.slider {
  -webkit-appearance: none;
  width: 100%;
  height: 25px;
  background: #d3d3d3;
  outline: none;
  opacity: 0.7;
  -webkit-transition: .2s;
  transition: opacity .2s;
  padding: 0px;
}

.slider:hover {
  opacity: 1;
}

.slider::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  width: 25px;
  height: 25px;
  background: #000000;
  cursor: pointer;
}

.slider::-moz-range-thumb {
  width: 25px;
  height: 25px;
  background: #000000;
  cursor: pointer;
}
</style>

<div id="tester" style="width:600px;height:500px;"></div>


Angular frequency ($\omega$)
<div class="slidecontainer" style="width:600px;height:25px;">
  <input type="range" min="0" max="99" value="49" class="slider" id="freqRange" onchange="computeSine(this.value)">
</div>

Phase ($\phi$)
<div class="slidecontainer" style="width:600px;height:25px;">
  <input type="range"  class="slider" min="0" max="99" value="49" id="phaseRange" onchange="computeSine(this.value)">
</div>

<script type="text/javascript">
  "use strict";

  var runtimeInit = false;

  var Module = {
      onRuntimeInitialized: function() {
          runtimeInit = true;
          plot();
      }
  };

  function computeSine(value) {
    if (runtimeInit) {
      console.log(_chl_sin(value));
    }
  }

  function plot() {
      "use strict";

      let TESTER = document.getElementById('tester');

      let size = 1000;

      // allocate memory for t and create a buffer from the heap
      let t_ptr = _calloc(size, Float32Array.BYTES_PER_ELEMENT);
      let t = new Float32Array(HEAPF32.buffer, t_ptr, size);

      let max = 1;

      for (let i = 0; i <= size; i++) {
          t[i] = i / size * max;
      }

      // allocate memory for x
      let x_ptr = _calloc(size, Float32Array.BYTES_PER_ELEMENT);

      let freq = 2*Math.PI;
      let phase = 0;

      _chl_sin_func(size, t_ptr, x_ptr, freq, phase);

      // create a buffer from x on the heap
      let x = new Float32Array(HEAPF32.buffer, x_ptr, size);

      let data = [{
          x: t,
          y: x
          }];

      let layout = {};

      Plotly.newPlot(TESTER, data, layout);
  }

</script>
<script type="text/javascript" src="https://cdn.plot.ly/plotly-2.6.3.min.js"></script>
<script type="text/javascript" src="{{ base.url | prepend: site.url }}/assets/js/chlsin.js"></script>
