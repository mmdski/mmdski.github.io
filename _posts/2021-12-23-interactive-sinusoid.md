---
layout: post
title: Interactive Sine Wave
tags:
- Wasm
- JavaScript
date: 2021-12-23 13:38 -0600
---
<script type="text/javascript" src="https://cdn.plot.ly/plotly-2.6.3.min.js"></script>
<style>
.sine-slider {
  width: 600px;
}
.ui-slider-handle.sine-handle {
  width: 5em;
  height: 1.6em;
  top: 50%;
  margin-top: -.8em;
  margin-left: -2.5em;
  text-align: center;
  line-height: 1.6em;
}
</style>

_edit: 2021-12-30_<br>
I've removed the sine function from the repository. The function can be found in this source file:
[chlsin.c](https://github.com/mmdski/mmdski.github.io/blob/0aa35e8143b0d53eb29cd85d7ff79b5e6ac0bd9b/chl/src/chlsin.c#L26){:target="_blank"}.

## Interactive example

Generally, a [sine wave](https://en.wikipedia.org/wiki/Sine_wave){:target="_blank"} as a function of time is

$$ f\left(t\right) = A\sin\left(\omega t + \phi\right) $$

where $A$ is the amplitude, $\omega$ is the angular frequency, and $\phi$ is the phase of the wave.

The following example starts with $A$ equal to 1, $\omega$ equal to $4\pi$, and $\phi$ equal to $0$. You can change the
values of these components with slider bars below the graph.

<div id="tester" style="width:600px;height:500px;"></div>
<br>
Amplitude ($A$)
<div id="ampSlider" class="sine-slider">
  <div id="ampHandle" class="ui-slider-handle sine-handle"></div>
</div>
<br>
Angular frequency ($\omega$)
<div id="freqSlider" class="sine-slider">
  <div id="freqHandle" class="ui-slider-handle sine-handle"></div>
</div>
<br>
Phase ($\phi$)
<div id="phaseSlider" class="sine-slider">
  <div id="phaseHandle" class="ui-slider-handle sine-handle"></div>
</div>

<script type="text/javascript">
  "use strict";

  var Module = {
      onRuntimeInitialized: function() {
          runPlot();
      }
  };

  function runPlot() {

    let size = 1000;
    let t_max = 1;

    // allocate memory for t and create a buffer from the heap
    let t_ptr = _calloc(size, Float32Array.BYTES_PER_ELEMENT);
    let t = new Float32Array(HEAPF32.buffer, t_ptr, size);

    for (let i = 0; i <= size; i++) {
        t[i] = i / size * t_max;
    }

    let nSliderValues = 1001; // odd so we can have a middle value
    let midSliderValue = (nSliderValues - 1)/2;

    let freq = [];
    let freqMin = 2*Math.PI;
    let freqMax = 6*Math.PI;
    let freqMid = (freqMax + freqMin)/2;
    let freqIndex = midSliderValue;

    let phase = [];
    let phaseMin = -Math.PI;
    let phaseMax = Math.PI;
    let phaseIndex = midSliderValue;

    let amplitude = 1;

    for (let i = 0; i <= nSliderValues; i++) {
      // make sure mid point is represented accurately
      freq.push((i - midSliderValue)/nSliderValues * (freqMax - freqMin) + freqMid);
      phase.push((i - midSliderValue)/nSliderValues * (phaseMax - phaseMin));
    }

    // allocate memory for x
    let x_ptr = _calloc(size, Float32Array.BYTES_PER_ELEMENT);

    _chl_sin_func(size, t_ptr, x_ptr, amplitude, freq[freqIndex], phase[phaseIndex]);

    // create a buffer from x on the heap
    let x = new Float32Array(HEAPF32.buffer, x_ptr, size);

    let TESTER = document.getElementById('tester');
    let data = [{x: t, y: x}];
    let layout = {width: 600, height: 500,
      margin: {b: 20, l: 50, r: 10, t: 10},
      dragmode: false,
      xaxis: {range: [0, 1], title: '$t$'},
      yaxis: {range: [-2.1, 2.1], title: '$f(t)$'}};
    Plotly.newPlot(TESTER, data, layout);

    function updatePlot() {
      _chl_sin_func(size, t_ptr, x_ptr, amplitude, freq[freqIndex], phase[phaseIndex]);
      let data_update = [{x: t, y: x}];
      Plotly.redraw(TESTER, data_update);
    }

    let ampHandle = $( "#ampHandle" );
    $( "#ampSlider" ).slider({
      min: 0,
      max: nSliderValues,
      value: midSliderValue,
      create: function() {
        ampHandle.text(amplitude.toPrecision(3));
      },
      slide: function(event, ui) {
        amplitude = 2 * ui.value / nSliderValues;
        ampHandle.text(amplitude.toPrecision(3));
        updatePlot();
      }
    });

    let freqHandle = $( "#freqHandle" );
    $( "#freqSlider" ).slider({
      min: 0,
      max: nSliderValues,
      value: midSliderValue,
      create: function() {
        freqHandle.text(freq[freqIndex].toPrecision(3));
      },
      slide: function(event, ui) {
        freqIndex = ui.value;
        freqHandle.text(freq[freqIndex].toPrecision(3));
        updatePlot();
      }
    });

    let phaseHandle = $( "#phaseHandle" );
    $( "#phaseSlider" ).slider({
      min: 0,
      max: nSliderValues,
      value: midSliderValue,
      create: function() {
        phaseHandle.text(phase[phaseIndex].toPrecision(3));
      },
      slide: function(event, ui) {
        phaseIndex = ui.value;
        phaseHandle.text(phase[phaseIndex].toPrecision(3));
        updatePlot();
      }
    });
  }
</script>

## Explanation
I created this example because I wanted to learn how to work with a graph that changes with user inputs. I'm not
completely satisfied with the results, but I consider it a good start. The code could use some cleaning up at the very
least.

The computation of the sine function is done in Wasm compiled with Emscripten, the plotting is done in Plotly, and the
slider bars come from [JQuery UI](https://jqueryui.com/){:target="_blank"}. I plan on working more with these libraries in the future, but
I'd like to add a library like [Bootstrap](https://getbootstrap.com/){:target="_blank"} to help with layout.
<script type="text/javascript" src="{{ base.url | prepend: site.url }}/assets/js/chlsin.js"></script>
