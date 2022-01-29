---
layout: post
title: Single Linear Reservoir
---

<script type="text/javascript" src="https://cdn.plot.ly/plotly-2.6.3.min.js"></script>

<style>
.slr-slider {
  width: 600px;
}
.ui-slider-handle.slr-handle {
  width: 5em;
  height: 1.6em;
  top: 50%;
  margin-top: -.8em;
  margin-left: -2.5em;
  text-align: center;
  line-height: 1.6em;
}
</style>


$$ \frac{dS}{dt} = I - Q $$

$$ S = KQ $$

$$ K\frac{dQ}{dt} = I - Q $$

[First order linear ordinary differential equation](https://en.wikipedia.org/wiki/Integrating_factor#Solving_first_order_linear_ordinary_differential_equations){:target="_blank"}

$$ \frac{dQ}{dt} + \frac{1}{K}Q = \frac{1}{K}I $$

$$ Q = e^{-\frac{t}{K}} \frac{1}{K} \int I e^{\frac{t}{K}} dt + C e^{-\frac{t}{K}} $$

$$ Q = Q_0e^{-\frac{t}{K}} + I\left(1 - e^{-\frac{t}{K}}\right) $$

<div id="tester" style="width:600px;height:500px;"></div>
<br>
Storage coefficient ($K$)
<div id="kSlider" class="slr-slider">
  <div id="kHandle" class="ui-slider-handle slr-handle"></div>
</div>
<br>
Initial flow ($Q_0$)
<div id="q0Slider" class="slr-slider">
  <div id="q0Handle" class="ui-slider-handle slr-handle"></div>
</div>
<br>
Inflow ($I$)
<div id="inflowSlider" class="slr-slider">
  <div id="inflowHandle" class="ui-slider-handle slr-handle"></div>
</div>

<script type="text/javascript">
  "use strict";

  let nSliderValues = 100;
  let midSliderValue = 50;

  // storage coefficient limits
  let minK = 5;
  let maxK = 65;
  let kStep = (maxK - minK) / nSliderValues;

  // initial flow limits
  let minQ0 = 0;
  let maxQ0 = 100;
  let q0Step = (maxQ0 - minQ0) / nSliderValues;

  // inflow limits
  let minInflow = 0;
  let maxInflow = maxQ0;
  let inflowStep = (maxInflow - minInflow) / nSliderValues;

  let kValues = [];
  let q0Values = [];
  let inflowValues = [];
  for (let i = 0; i <= nSliderValues; i++) {
      kValues.push(minK + i * kStep);
      q0Values.push(minQ0 + i * q0Step);
      inflowValues.push(minInflow + i * inflowStep);
  }
  let K = kValues[midSliderValue];
  let initialFlow = q0Values[midSliderValue];
  let inflow = inflowValues[0];

  let nTimes = 1000;
  let maxTime = 480;
  let timeStep = maxTime / (nTimes + 1);

  let flow = [];
  let time = [];

  for (let i = 0; i < nTimes; i++) {
      time.push(timeStep * i);
      flow.push(0);
  }

  calcFlow();

  let TESTER = document.getElementById('tester');
  let data = [{x: time, y: flow}];
  let layout = {width: 600, height: 500,
    margin: {b: 20, l: 50, r: 10, t: 10},
    dragmode: false,
    xaxis: {range: [0, maxTime], title: '$t$'},
    yaxis: {range: [0, 1.01*maxQ0], title: '$Q$'}};
  Plotly.newPlot(TESTER, data, layout);

  function calcFlow() {
      for (let i = 0; i < nTimes; i++) {
          flow[i] = initialFlow * Math.exp(-time[i]/K) + inflow * (1 - Math.exp(-time[i]/K));
      }
  }

  function updatePlot() {
    calcFlow();
    let data_update = [{x: time, y: flow}];
    Plotly.redraw(TESTER, data_update);
  }

  let kHandle = $( "#kHandle" );
  $( "#kSlider" ).slider({
    min: 0,
    max: nSliderValues,
    value: midSliderValue,
    create: function() {
      kHandle.text(K.toPrecision(3));
    },
    slide: function(event, ui) {
      K = kValues[ui.value];
      kHandle.text(K.toPrecision(3));
      updatePlot();
    }
  });
  let q0Handle = $( "#q0Handle" );
  $( "#q0Slider" ).slider({
    min: 0,
    max: nSliderValues,
    value: midSliderValue,
    create: function() {
      q0Handle.text(initialFlow.toPrecision(3));
    },
    slide: function(event, ui) {
      initialFlow = q0Values[ui.value];
      q0Handle.text(initialFlow.toPrecision(3));
      updatePlot();
    }
  });
  let inflowHandle = $( "#inflowHandle" );
  $( "#inflowSlider" ).slider({
    min: 0,
    max: nSliderValues,
    value: 0,
    create: function() {
      inflowHandle.text(inflow.toPrecision(3));
    },
    slide: function(event, ui) {
      inflow = inflowValues[ui.value];
      inflowHandle.text(inflow.toPrecision(3));
      updatePlot();
    }
  });
</script>
