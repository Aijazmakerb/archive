#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

void setup()
{
  Serial.begin(9600);
  mySerial.begin(115200);
}

void loop()
{
  if(mySerial.available())
  {
    String receivedData = mySerial.readStringUntil('\n');
    Serial.println(receivedData);
  }
}
