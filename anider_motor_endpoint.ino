#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Realme X";
const char* password = "12345678";

ESP8266WebServer server(5030);
const int MOTOR_PIN = D2;

void motorRun(int delayValue) 
{
  Serial.println("Delay value: " + String(delayValue));
  String json ="{";
  json += "\"message\":Motor turned on}";
  digitalWrite(MOTOR_PIN, LOW);
  server.send(200, "application/json", json);
  delay(delayValue);
  digitalWrite(MOTOR_PIN, HIGH);
}

void motorStop()
{
  String json ="{";
  json += "\"message\":Motor turned off}";
  digitalWrite(MOTOR_PIN, HIGH);
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, HIGH);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  
  Serial.println(WiFi.localIP());

  server.on("/motor/on", [](){
  int delayValue = server.arg("delay").toInt();
  motorRun(delayValue);
  });
  server.on("/motor/off", motorStop);
  server.begin();
  Serial.println("HTTP server started");
}
void loop()
{
  server.handleClient();
  delay(500);
}
