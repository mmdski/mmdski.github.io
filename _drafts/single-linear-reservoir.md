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
    justify-self: center;
  }
</style>

When I took a surface hydrology course, the linear reservoir concept was introduced as a simple
[runoff model](https://en.wikipedia.org/wiki/Runoff_model_(reservoir)){:target="_blank"} for a watershed. A linear
reservoir is a reservoir with a storage $S$ that is
[directly proportional](https://en.wikipedia.org/wiki/Proportionality_(mathematics)#Direct_proportionality){:target="_blank"}
to the reservoir outflow $Q$,

$$ S = KQ. $$

$S$ has the dimension of volume ($L^3$) and $Q$ has the dimension of volume per unit time ($L^3T^{-1}$). The
proportionality constant $K$ is known as the storage coefficient[^1] and has the dimension of time ($T$). This
relation can be combined with the continuity equation,

$$ \frac{dS}{dt} = I - Q, $$

where $I$ is the reservoir inflow, to obtain a first order linear ordinary differential equation (ODE),

$$ \frac{dQ}{dt} + \frac{1}{K}Q = \frac{1}{K}I. $$

This ODE can be solved using an [integration factor](https://en.wikipedia.org/wiki/Integrating_factor#Solving_first_order_linear_ordinary_differential_equations){:target="_blank"},

$$ Q\left(t\right) = e^{-\int\frac{1}{K} dt} \frac{1}{K} \int I e^{\int \frac{1}{K} dt} dt + C e^{-\frac{t}{K}}. $$

Setting $Q\left(0\right) = Q_0$ and requiring $I$ to be constant through time yields

$$ Q\left(t\right) = Q_0e^{-\frac{t}{K}} + I\left(1 - e^{-\frac{t}{K}}\right). $$

The solution to this equation is shown in the figure below. You can adjust the parameters to the solution by using the
slider bars to the left, right, and below the figure. The left slider modifies the initial inflow $Q_0$, the right
slider modifies the reservoir inflow $I$, and the slider below the figure modifies the storage coefficient $K$.

<div class="container">
  <div id="q0Slider" class="initial-flow-slider"></div>
  <div id="tester" class="plot-area"></div>
  <div id="inflowSlider" class="inflow-slider"></div>
  <div id="k-value" class="k-value"></div>
  <div id="kSlider" class="slr-horizontal-slider"></div>
</div>
<br>

[^1]: Pedersen, J. T., Peters, J. C., & Helweg, O. J. (1980). Hydrographs by Single Linear Reservoir Model. Hydrologic Engineering Center Davis, CA. [https://www.hec.usace.army.mil/publications/TechnicalPapers/TP-74.pdf](https://www.hec.usace.army.mil/publications/TechnicalPapers/TP-74.pdf){:target="_blank"}

<script type="text/javascript">
  "use strict";

  let nTimes = 1000;
  let maxTime = 480;
  let timeStep = maxTime / (nTimes + 1);

  let time = [];

  for (let i = 0; i < nTimes; i++) {
      time.push(timeStep * i);
  }

  let nSliderValues = 100;
  let midSliderValue = 50;

  // storage coefficient limits
  let minK = 1;
  let maxK = time[nTimes - 1]/2;

  // initial flow limits
  let minQ0 = 0;
  let maxQ0 = 100;

  // inflow limits
  let minInflow = 0;
  let maxInflow = maxQ0;

  let kValues = [];
  let q0Values = [];
  let inflowValues = [];
  let frac = 0;
  for (let i = 0; i < nSliderValues; i++) {
      frac = i/(nSliderValues - 1);
      kValues.push(minK + frac * maxK);
      q0Values.push(minQ0 + frac * maxQ0);
      inflowValues.push(minInflow + frac * maxInflow);
  }
  let K = kValues[midSliderValue];
  let initialFlow = q0Values[nSliderValues - 1];
  let inflow = inflowValues[0];

  let flow = calcFlow(K, initialFlow, inflow, time);

  let TESTER = document.getElementById('tester');
  let data = [
    {
      x: time,
      y: flow,
      name: 'Outflow'
    },
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
    max: nSliderValues - 1,
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
    max: nSliderValues - 1,
    value: nSliderValues - 1,
    slide: function(event, ui) {
      initialFlow = q0Values[ui.value];
      updatePlot();
    }
  });
  let inflowHandle = $( "#inflowHandle" );
  $( "#inflowSlider" ).slider({
    orientation: "vertical",
    min: 0,
    max: nSliderValues - 1,
    value: 0,
    slide: function(event, ui) {
      inflow = inflowValues[ui.value];
      updatePlot();
    }
  });
</script>
