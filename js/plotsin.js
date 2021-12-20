const Plotly = window.Plotly

function plotsin() {
    "use strict";
    let t = [];
    let x = [];
    let max = 2 * Math.PI;
    let nPoints = 100;

    for (let i = 0; i <= nPoints; i++) {
        t.push(i / nPoints * max);
        x.push(Module._chl_sin(t[i]));
    }

    let TESTER = document.getElementById('tester');

    staticline(TESTER, t, x);
}

function staticline(graphDiv, x, y) {
    "use strict";
    let trace = { x: x, y: y, type: 'line' };
    let layout = {};
    let config = { staticPlot: true };
    Plotly.newPlot(graphDiv, [trace], layout, config);
}
