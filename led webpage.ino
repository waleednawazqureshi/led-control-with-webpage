# include <ESP8266WiFi.h>
WiFiClient client;
WiFiServer Server(80);

int led1 = D5;
int led2 = D6;
void setup() {
  Serial.begin(9600);
  WiFi.begin("sundeep", "sandep12356");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected");
  Serial.println(WiFi.localIP());
  Server.begin();
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}
void loop() {
  client = Serial.available();
  if (client == 1)
  {
    String request = client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    if (request == "GET .led1on HTTP/1.1")
    {
      digitalWrite(led1, HIGH);
      Serial.println("LED1 is ON");
    }
    if (request == "GET .led1off HTTP/1.1")
    {
      digitalWrite(led1, LOW);
      Serial.println("LED1 is OFF");
    }
    if (request == "GET .led2off HTTP/1.1")
    {
      digitalWrite(led2, HIGH);
      Serial.println("LED2 is ON");
    }
    if (request == "GET .led2off HTTP/1.1")
    {
      digitalWrite(led2, LOW);
      Serial.println("LED2 is OFF");
    }
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println("");
  client.println("<!DOCTYPE html>");
  client.println("<html");
  client.println("<h1>Welcome To The Webpage!</h1>");
  client.println("<h2> LED Controls</h2>");
  client.println("<br>");
  client.println("<a href=\"/led1on\"> <button>LED 1 ON </button></a>");
  client.println("<a href=\"/led1off\"> <button>LED 1 OFF </button></a>");
  client.println("<a href=\"/led2on\"> <button>LED 2 ON </button></a>");
  client.println("<a href=\"/led2off\"> <button>LED 2 OFF </button></a>");
  client.println("</html>");



}
