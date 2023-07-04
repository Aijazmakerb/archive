//Serial Communication
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);

//SD card module and wav file player
#include <SD.h>
#include <TMRpcm.h>
#include <SPI.h>
#define SD_CS_PIN 10
#define SPEAKER_PIN 9

TMRpcm tmrpcm;

//IR
int IR1 = 2;
int IR2 = 3;

//Motors

// Motor A connections
int motorAPin1 = 4;
int motorAPin2 = 5;
int motorASpeedPin = 9; // PWM pin for controlling motor speed (analog pin)

// Motor B connections
int motorBPin1 = 6;
int motorBPin2 = 7;
int motorBSpeedPin = 10;

void setup()
{
  //Starting the serial communication between the uno and node mcu 
  Serial.begin(9600);
  mySerial.begin(115200);

  //Creating sd card module instance
  tmrpcm.speakerPin = SPEAKER_PIN;
  tmrpcm.setVolume(6);
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD card initialization failed!");
    return;
  }

  //Estabilishing IR connection
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  // Setting motor pins as outputs
  pinMode(motorAPin1, OUTPUT);
  pinMode(motorAPin2, OUTPUT);
  pinMode(motorASpeedPin, OUTPUT);
  pinMode(motorBPin1, OUTPUT);
  pinMode(motorBPin2, OUTPUT);
  pinMode(motorBSpeedPin, OUTPUT);
}

void loop()
{
  //Maintaining IR value
  int irSensor1value = digitalRead(IR1);
  int irSensor2value = digitalRead(IR2);
  if(mySerial.available())
  {
    String receivedData = mySerial.readStringUntil('\n');
    Serial.println(receivedData);
    if(receivedData != nullptr)
    {
      if(receivedData == "1")
      {
        tmrpcm.play("audio1.wav");
        Serial.println("PlayingAudio");
      }else if(receivedData == "2")
      {
        tmrpcm.play("audio2.wav");
      }else if(receivedData == "3")
      {
        tmrpcm.play("audio3.wav");
      }
      else if(receivedData == "4")
      {
        tmrpcm.play("audio4.wav");
      }else if(receivedData == "5")
      {
        tmrpcm.play("audio5.wav");
      }else if(receivedData == "6")
      {
        tmrpcm.play("audio6.wav");
      }else if(receivedData == "7")
      {
        tmrpcm.play("audio7.wav");
      }else if(receivedData == "8")
      {
        tmrpcm.play("audio8.wav");
      }
      else if(receivedData == "9")
      {
        tmrpcm.play("audio9.wav");
      }else if(receivedData == "10")
      {
        tmrpcm.play("audio10.wav");
      }else if(receivedData == "F" && irSensor1value < 1 && irSensor2value < 1) //Controlling motor driver from here
      {
        moveForward();
      }else if(receivedData == "B")
      {
        moveBackward();
      }else if(receivedData == "L")
      {
        turnLeft();
      }else if(receivedData == "R")
      {
        turnRight();
      }
    }
  }
}

void moveForward()
{
  // Motor A
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorAPin2, LOW);
  analogWrite(motorASpeedPin, 128);  // Set motor A speed to half

  // Motor B
  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, LOW);
  analogWrite(motorBSpeedPin, 128);  // Set motor B speed to half
}

void moveBackward()
{
  // Motor A
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, HIGH);
  analogWrite(motorASpeedPin, 128);  // Set motor A speed to half

  // Motor B
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, HIGH);
  analogWrite(motorBSpeedPin, 128);  // Set motor B speed to half
}

void turnLeft()
{
  // Motor A
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, HIGH);
  analogWrite(motorASpeedPin, 128);  // Set motor A speed to half

  // Motor B
  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, LOW);
  analogWrite(motorBSpeedPin, 128);  // Set motor B speed to half
}

void turnRight()
{
  // Motor A
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorAPin2, LOW);
  analogWrite(motorASpeedPin, 128);  // Set motor A speed to half

  // Motor B
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, HIGH);
  analogWrite(motorBSpeedPin, 128);  // Set motor B speed to half
}
