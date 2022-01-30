---
layout: post
title: Single Linear Reservoir
---

<script type="text/javascript" src="https://cdn.plot.ly/plotly-2.6.3.min.js"></script>

<style>
  .container {
    display: grid;
    grid-gap: 20px;
  }
  .slr-horizontal-slider {
    width: 550px;
    grid-column: 2;
    grid-row: 3;
    justify-self: center;
  }
  .k-value {
    grid-column: 2;
    grid-row: 2;
    justify-self: center;
  }
  .initial-flow-slider {
    height: 465px;
    grid-column: 1;
    grid-row: 1;
    align-self: center;
  }
  .inflow-slider {
    height: 465px;
    grid-column: 3;
    grid-row: 1;
    align-self: center;
  }
  .plot-area {
    height: 500px;
    width: 600px;
    grid-column: 2;
    grid-row: 1;
    align-self: center;
    justify-self: end;
  }
</style>


$$ \frac{dS}{dt} = I - Q $$

$$ S = KQ $$

$$ K\frac{dQ}{dt} = I - Q $$

[First order linear ordinary differential equation](https://en.wikipedia.org/wiki/Integrating_factor#Solving_first_order_linear_ordinary_differential_equations){:target="_blank"}

$$ \frac{dQ}{dt} + \frac{1}{K}Q = \frac{1}{K}I $$

$$ Q = e^{-\frac{t}{K}} \frac{1}{K} \int I e^{\frac{t}{K}} dt + C e^{-\frac{t}{K}} $$

$$ Q = Q_0e^{-\frac{t}{K}} + I\left(1 - e^{-\frac{t}{K}}\right) $$

<div class="container">
  <div id="q0Slider" class="initial-flow-slider"></div>
  <div id="tester" class="plot-area"></div>
  <div id="inflowSlider" class="inflow-slider"></div>
  <div id="k-value" class="k-value"></div>
  <div id="kSlider" class="slr-horizontal-slider"></div>
</div>

<script type="text/javascript">
  "use strict";

  let nSliderValues = 100;
  let midSliderValue = 50;

  let nTimes = 1000;
  let maxTime = 480;
  let timeStep = maxTime / (nTimes + 1);

  let time = [];

  for (let i = 0; i < nTimes; i++) {
      time.push(timeStep * i);
  }

  // storage coefficient limits
  let minK = time[0];
  let maxK = time[nTimes - 1];
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

  let flow = calcFlow(K, initialFlow, inflow, time);

  let TESTER = document.getElementById('tester');
  let data = [
    {x: time, y: flow, name: 'Outflow'},
    {
      x: [time[0]],
      y: [initialFlow],
      mode: 'markers',
      marker: {size: 10},
      name: 'Initial Flow'
    },
    {
      x: [time[0], time[nTimes - 1]],
      y: [inflow, inflow],
      mode: 'lines',
      name: 'Inflow'
    }
  ];
  let layout = {width: 600, height: 500,
    margin: {b: 20, l: 50, r: 10, t: 10},
    legend: { x: 1,
      xanchor: 'right',
      y: 1,
      bgcolor: '#FFFFFF',
      bordercolor: '#000000',
      borderwidth: 1},
    dragmode: false,
    xaxis: {range: [0, maxTime], title: '$t$'},
    yaxis: {range: [0, 1.01*maxQ0], title: '$Q$'}};
  Plotly.newPlot(TESTER, data, layout);

  let kValue = document.getElementById("k-value");
  kValue.textContent = "K = " + K.toPrecision(3);

  function calcFlow(K, initialFlow, inflow, time) {
    let flow = [];
    for (let i = 0; i < nTimes; i++) {
        flow.push(initialFlow * Math.exp(-time[i]/K) + inflow * (1 - Math.exp(-time[i]/K)));
    }
    return flow;
  }

  function updatePlot() {
    let flow = calcFlow(K, initialFlow, inflow, time);
    let flow_update = {
      x: [time, [time[0]], [time[0], time[nTimes - 1]]],
      y: [flow, [initialFlow], [inflow, inflow]]
    };
    Plotly.restyle(TESTER, flow_update);
  }

  let kHandle = $( "#kHandle" );
  $( "#kSlider" ).slider({
    min: 0,
    max: nSliderValues,
    value: midSliderValue,
    slide: function(event, ui) {
      K = kValues[ui.value];
      kValue.textContent = "K = " + K.toPrecision(3);
      updatePlot();
    }
  });
  let q0Handle = $( "#q0Handle" );
  $( "#q0Slider" ).slider({
    orientation: "vertical",
    min: 0,
    max: nSliderValues,
    value: midSliderValue,
    slide: function(event, ui) {
      initialFlow = q0Values[ui.value];
      updatePlot();
    }
  });
  let inflowHandle = $( "#inflowHandle" );
  $( "#inflowSlider" ).slider({
    orientation: "vertical",
    min: 0,
    max: nSliderValues,
    value: 0,
    slide: function(event, ui) {
      inflow = inflowValues[ui.value];
      updatePlot();
    }
  });
</script>
