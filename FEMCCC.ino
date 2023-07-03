#include <Servo.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "FEMCCC";

const char index_html[] PROGMEM = {"<html>\n  <body>\n    <h1>Hello from Aijaz</h1>\n    <input type=\"text\" name=\"data\" placeholder=\"Enter Data\" />\n    <button onclick=\"SendData()\">Send Data</button>\n    <script>\n      function SendData() {\n        var data = document.getElementsByName(\"data\")[0].value;\n        window.location.href = \"/?data=\" + encodeURIComponent(data);\n      }\n    </script>\n  </body>\n</html>"};

ESP8266WebServer server(80);

String recievedData;

Servo myServo;

void handleRoot()
{
  if(server.hasArg("data")){
    recievedData = server.arg("data");
    Serial.print("Recieved Data : ");
    Serial.println(recievedData);
  }
  server.send_P(200, "text/html", index_html);
}

void setup()
{
  //Starting the serial communication
  Serial.begin(115200);
  //Stabilishing the wifi connection
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  //Finding and printing the ip
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);
  //Assigning the web server on domain index path
  server.on("/", handleRoot);
  //Starting the server
  server.begin();
  Serial.println("Web server started");
  //Initializing the servo
  myServo.attach(2);
  myServo.write(180);
  delay(1000);
  myServo.write(0);
}

void loop()
{
  server.handleClient();

  if (!recievedData.isEmpty()) {
    // Perform operations or logic based on the received data
    if (recievedData == "F") {
      myServo.write(90);
    } else if (recievedData == "B") {
      myServo.write(0);
    }

    // Reset the receivedData variable after processing
    recievedData = "";
  }
}
