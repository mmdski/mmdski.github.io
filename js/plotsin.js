const Plotly = window.Plotly

function plotsin() {
    var t = [];
    var x = [];
    var max = 2 * Math.PI;
    var nPoints = 100;

    // chl_sin = Module.cwrap('chl_sin', 'number', ['number']);

    for (var i = 0; i <= nPoints; i++) {
        t.push(i / nPoints * max);
        // x.push(Math.sin(t[i]))
        x.push(Module._chl_sin(t[i]));
    }

    TESTER = document.getElementById('tester');

    var trace = { x: t, y: x, type: 'line' };
    var config = { hovermode: false, margin: { t: 0 }, displayModeBar: false };

    Plotly.newPlot(TESTER, [trace], config);
}
