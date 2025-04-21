//Archivo de prueba de vuelo
//al incrementar el pwm cambia el color

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Mark01_Net";
const char* password = "droneproject";

WebServer server(80);

const int motorPin = 5;
const int ledPin = 8;
int pwmValue = 0;

void handleRoot() {
  #ifdef RGB_BUILTIN
  int rpm = map(pwmValue, 0, 255, 0, 25000);
  Serial.println("AP listo: http://192.168.4.1");
  Serial.println("RPM: " + rpm);
  if (pwmValue ==0){
        rgbLedWrite(RGB_BUILTIN, 0, 0, 0);  // Off / black
  }
  if(pwmValue >0 & pwmValue <100){
    rgbLedWrite(RGB_BUILTIN, 0, 0, RGB_BRIGHTNESS);  // Blue
  }
  if(pwmValue >=100 & pwmValue <200){
    rgbLedWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, 0);  // Green
  }
  if (pwmValue >199){
    rgbLedWrite(RGB_BUILTIN, RGB_BRIGHTNESS, 0, 0);  // Red
  }
  #endif
  String scriptGauge = R"rawliteral(
<script>
class Gauge {
  constructor(t) {
    this.maxValue = t.maxValue || 100;
    this.minValue = t.minValue || 0;
    this.value = this.minValue;
    this.speed = t.animationSpeed || 32;
    this.canvas = t.renderTo;
    this.ctx = this.canvas.getContext("2d");
    this.draw();
  }
  set(t) {
    this.value = Math.max(this.minValue, Math.min(this.maxValue, t));
    this.draw();
  }
  draw() {
    const t = this.canvas.width / 2, e = this.canvas.height;
    const n = this.ctx, a = Math.PI * 0.75, r = Math.PI * 0.25;
    const o = this.value / (this.maxValue - this.minValue);
    n.clearRect(0, 0, this.canvas.width, this.canvas.height);
    n.beginPath();
    n.arc(t, e, 100, a, r, false);
    n.lineWidth = 20;
    n.strokeStyle = "#ccc";
    n.stroke();
    let i = a + (r - a) * o;
    n.beginPath();
    n.moveTo(t, e);
    n.lineTo(t + 90 * Math.cos(i), e + 90 * Math.sin(i));
    n.lineWidth = 4;
    n.strokeStyle = "#f00";
    n.stroke();
    n.font = "20px Arial";
    n.fillStyle = "#000";
    n.textAlign = "center";
    n.fillText(Math.round(this.value) + " RPM", t, e + 60);
  }
}
</script>
)rawliteral";

  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Mark01 - Velocímetro</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: sans-serif; text-align: center; padding: 20px; background: #f5f5f5; }
    canvas { max-width: 300px; }
    .container { max-width: 400px; margin: auto; background: white; padding: 20px; border-radius: 15px; box-shadow: 0 0 10px rgba(0,0,0,0.2); }
    input[type=range] { width: 100%; margin-top: 15px; }
  </style>
</head>
<body>
  <div class="container">
    <h2>Motor A - Mark01</h2>
    <canvas id="gauge" width="300" height="150"></canvas>
    <form action="/set" method="get">
      <input type="range" min="0" max="255" name="value" value="%PWM%" oninput="sliderVal.value = this.value">
      <input type="number" name="value" id="sliderVal" min="0" max="255" value="%PWM%" onchange="this.previousElementSibling.value = this.value">
      <br><br>
      <input type="submit" value="Actualizar PWM">
    </form>
  </div>
  <script>
    const g = new Gauge({ renderTo: document.getElementById("gauge"), maxValue: 25000, animationSpeed: 32 });
    g.set(%RPM%);
  </script>
%GAUGE_SCRIPT%
</body>
</html>
)rawliteral";

  html.replace("%PWM%", String(pwmValue));
  html.replace("%RPM%", String(rpm));
  html.replace("%GAUGE_SCRIPT%", scriptGauge);
  server.send(200, "text/html", html);

}

void handleSet() {
  if (server.hasArg("value")) {
    pwmValue = constrain(server.arg("value").toInt(), 0, 255);
    analogWrite(motorPin, pwmValue);
    analogWrite(ledPin, pwmValue);
  }
  handleRoot();
}

void setup() {
  Serial.begin(115200);
  pinMode(motorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  analogWrite(motorPin, 0);
  analogWrite(ledPin, 0);

  WiFi.softAP(ssid, password);
  Serial.println("AP listo: http://192.168.4.1");

  server.on("/", handleRoot);
  server.on("/set", handleSet);
  server.begin();
}

void loop() {
  server.handleClient();
}
