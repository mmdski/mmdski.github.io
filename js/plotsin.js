const Plotly = window.Plotly

function plotsin() {
    var t = [];
    var x = [];
    var max = 2 * Math.PI;
    var nPoints = 100;

    for (var i = 0; i <= nPoints; i++) {
        t.push(i / nPoints * max);
        x.push(Module._chl_sin(t[i]));
    }

    TESTER = document.getElementById('tester');

    staticline(TESTER, t, x);
}

function staticline(graphDiv, x, y) {
    var trace = { x: x, y: y, type: 'line' };
    var layout = {};
    var config = { staticPlot: true };
    Plotly.newPlot(graphDiv, [trace], layout, config);
}
