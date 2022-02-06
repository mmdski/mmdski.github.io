---
layout: post
title: Single Linear Reservoir (Part 2)
tags: ["linear reservoir", "single linear reservoir", "ode"]
---
<script type="text/javascript" src="https://cdn.plot.ly/plotly-2.6.3.min.js"></script>

I've [briefly discussed]({% post_url 2022-01-30-single-linear-reservoir %}) the single linear reservoir model for
runoff, but the information I presented wasn't the most useful for developing a runoff hydrograph since reservoir inflow
$I$ was constant over the time period shown in the plot.

If the initial time of a time period is $t_0$, the time inflow starts is $t_1$, and the time inflow stops is $t_2$, and
$Q_0=Q\left(t_0\right)$, $Q_1=Q\left(t_1\right)$, and $Q_2=Q\left(t_2\right)$, then the equation for outflow is

$$ Q\left(t\right) = \begin{cases}
    Q_0e^{-\frac{t}{K}}& \text{if $t \le t_1$},\\
    Q_1e^{-\frac{t - t_1}{K}} + I\left(1 - e^{-\frac{t - t_1}{K}}\right)& \text{if $t_1 < t \le t_2$},\\
    Q_2e^{-\frac{t - t_2}{K}}& \text{if $t_2 < t.$}
\end{cases}$$

The plot below has an adjustable period of inflow. The range slider below the storage coefficient ($K$) slider adjusts
the period. The time period between the slider handles is the inflow time period. The left slider sets $t_1$ and the
right slider sets $t_2$. The sliders begin so that $t_1=t_0$.

The other sliders are the same as in the previous post. The left slider modifies the initial inflow $Q_0$, the right
slider modifies the reservoir inflow $I$, and the slider below the figure modifies the storage coefficient $K$.

This is starting to look more like a [hydrograph](https://en.wikipedia.org/wiki/Hydrograph){:target="_blank"}, but
there's still room for improvement.

<style>
  .container {
    display: grid;
    grid-gap: 20px;
  }
  .k-value {
    grid-column: 2;
    grid-row: 2;
    justify-self: center;
  }
  .k-slider {
    width: 550px;
    grid-column: 2;
    grid-row: 3;
    justify-self: center;
  }
  .t1-slider {
    width: 550px;
    grid-column: 2;
    grid-row: 4;
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

<div class="container">
  <div id="q0Slider" class="initial-flow-slider"></div>
  <div id="tester" class="plot-area"></div>
  <div id="inflowSlider" class="inflow-slider"></div>
  <div id="k-value" class="k-value"></div>
  <div id="k-slider" class="k-slider"></div>
  <div id="t1-slider" class="t1-slider"></div>
</div>
<br>

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
  let midSliderValue = Math.trunc(nSliderValues/2);

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
  let initialFlow = q0Values[0];
  let inflowValue = inflowValues[Math.trunc(2/3*nSliderValues)];

  let t1 = time[0];
  let t2 = time[nTimes/2];

  let inflowTS = calcInflowTS();
  let flow = calcFlow();

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
      x: time,
      y: inflowTS,
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

  function calcInflowTS() {
    let inflowTS = [];
    for (let i = 0; i < nTimes; i++) {
      if (time[i] < t1) {
        inflowTS.push(0);
      }
      else if (time[i] <= t2) {
        inflowTS.push(inflowValue);
      } else {
        inflowTS.push(0);
      }
    }

    return inflowTS;
  }

  function calcFlow() {
    let flow = [];

    // first time step
    flow.push(initialFlow);

    let Q;
    let I;
    for (let i = 1; i < nTimes; i++) {
        Q = flow[i - 1];
        I = inflowTS[i];
        flow.push(Q * Math.exp(-timeStep/K) + I * (1 - Math.exp(-timeStep/K)));
    }
    return flow;
  }

  function updatePlot() {
    let flow = calcFlow();
    let flow_update = {
      x: [time, [time[0]], time],
      y: [flow, [initialFlow], inflowTS]
    };
    Plotly.restyle(TESTER, flow_update);
  }

  $( "#k-slider" ).slider({
    min: 0,
    max: nSliderValues - 1,
    value: midSliderValue,
    slide: function(event, ui) {
      K = kValues[ui.value];
      kValue.textContent = "K = " + K.toPrecision(3);
      updatePlot();
    }
  });
  $( "#t1-slider" ).slider({
    range: true,
    min: 0,
    max: nTimes,
    values: [0, nTimes/2],
    slide: function(event, ui) {
      t1 = time[ui.values[0]]
      t2 = time[ui.values[1] - 1];
      inflowTS = calcInflowTS();
      updatePlot();
    }
  });
  $( "#q0Slider" ).slider({
    orientation: "vertical",
    min: 0,
    max: nSliderValues - 1,
    value: 0,
    slide: function(event, ui) {
      initialFlow = q0Values[ui.value];
      updatePlot();
    }
  });
  $( "#inflowSlider" ).slider({
    orientation: "vertical",
    min: 0,
    max: nSliderValues - 1,
    value: 2/3*nSliderValues,
    slide: function(event, ui) {
      inflowValue = inflowValues[ui.value];
      inflowTS = calcInflowTS();
      updatePlot();
    }
  });
</script>
