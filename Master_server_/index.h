const char MAIN_page[] PROGMEM = R"webpage(
<!DOCTYPE HTML><html>
<head>
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/css/materialize.min.css">
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<script src="https://code.highcharts.com/8.0/highcharts.js"></script>

<style>
.container{
  min-width: 300px;
  max-width: 1000px;
  height: 500px;
  margin: 15px;
  }
h2 {
    text-align: center;
}

.titulo{
  background-color: #b9f6ca;
  border-radius: 70px;
  width: 700px;
  margin: 0 auto;
  }
.normal{
     max-width: 150px;
     min-height: 50px;
     background: #e0e0e0 ;
     padding: 10px;
     box-sizing: border-box;
     color: #FFF;
     margin: 20px;
     box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.75);
  }

.disturbio{
     max-width: 150px;
     min-height: 50px;
     background: #e0e0e0;
     padding: 10px;
     box-sizing: border-box;
     color: #FFF;
     margin: 20px;
     box-shadow: 0px 2px 18px -4px rgba(0, 0, 0, 0.75);
  }
.indica_dist{
  position: absolute;
  top:200px;
  right:100px;
  }
</style>
</head>
<body>

<div class="tudo">
<div class="titulo"><h2>Sensor de vibração Grendene</h2></div>
<div id="Acx-chart" class="container"></div>
<div class = "indica_dist">
<div id="normal_bloco" class="normal">
<h4><font color="#212121">Normal</font></h4>
</div>
<div id="dist_bloco" class="disturbio">
<h4><font color="#212121">Distúrbio !!!</font></h4>
</div>
</div>
</div>
</body>
<script>
    var chartT = new Highcharts.Chart({
    chart:{ renderTo : 'Acx-chart' },
    title: { text: 'Monitoramento em tempo real sensor' },
    series: [{
    name: 'Acx',
    color: '#0277bd', 
    data: []
  }, {
    name:'Acy',
    color: '#64dd17 ',
    data: []
  }, {
    name:'Acz',
    color: '#b71c1c',
    data: []  
  }],

  xAxis: { type: 'datetime',
    dateTimeLabelFormats: { second: '%H:%M:%S' }
  },
  yAxis: {
    title: { text: 'Acelerômetro dados' }
  },
  credits: { enabled: false }
});

          setInterval(function () {
          var xhttp = new XMLHttpRequest();
          xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            var sensors = JSON.parse(this.responseText);
            var x = (new Date()).getTime();
            var y = sensors.Acx;
            var z = sensors.Acy;
            var w = sensors.Acz;
          if(chartT.series[0].data.length > 600) {
             chartT.series[0].addPoint([x, y], true, true, true);
             chartT.series[1].addPoint([x, z], true, true, true);
             chartT.series[2].addPoint([x, w], true, true, true); 
          } else {
            chartT.series[0].addPoint([x, y], true, false, true);
            chartT.series[1].addPoint([x, z], true, false, true);
             chartT.series[2].addPoint([x, w], true, false, true);
          }
          }
          };
          xhttp.open("GET", "/acx", true);
          xhttp.send();
          }, 10 ) ;

setInterval(function() {
  var xhttp = new XMLHttpRequest();
  xhttp.open("GET", "/botoes", true);
  xhttp.send();
  xhttp.onload = function() {
    if (this.status == 200) {
      var jsonResponse = JSON.parse(this.responseText);
      if (jsonResponse.Indica_normal == '1'){
        document.getElementById("normal_bloco").style.backgroundColor = '#02b875';
        document.getElementById("dist_bloco").style.backgroundColor = '#e0e0e0';
        }
      if (jsonResponse.Indica_dist1 == '1'){
        document.getElementById("dist_bloco").style.backgroundColor = '#d84315';
        document.getElementById("normal_bloco").style.backgroundColor = '#e0e0e0';
        }
    }
    else {
      console.log(this.status);
    }
  };
}, 10); 


</script>
</html>)webpage";
