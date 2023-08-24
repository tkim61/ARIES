
// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>
// modified by Thomas Kim

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006
//modified 6/29/2022

// This example code is in the public domain.

// 04-Feb-2018 mcarter adapted
//RPi:SDA/GPIO8 --> ESP32:GREEN/"RX"/GPIO26/28
//RPi:SCL/GPIO9 --> ESP32:ORANGE/"TX"/GPIO17/10

#include <ArduinoJson.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

#define RPi_SDA 26
#define RPi_SCL 17
const uint8_t follower_address = 0x08;
const uint32_t freq = 100000;
static_assert(LOW == 0, "Expecting LOW to be 0");

int tum, back, leftCheek, rightCheek, head;
sensors_event_t a, g, temp; //a is accel, g is gyro, in x, y , and z
char c;

TwoWire mpuWire = TwoWire(0);
StaticJsonDocument<128> doc;
char response[128];

uint32_t i = 0;

void setup() {
  Serial.begin(115200);
  Wire1.onReceive(receiveEvent); // what to do when we get a write
  Wire1.onRequest(requestEvent); //what to do when we get a read
  
  if(!Wire1.begin(follower_address, RPi_SDA, RPi_SCL, freq)){
    Serial.println("failed to set up Pi comm channel");
  }

  
//  mpuWire.begin(21,22,100000);

  
  if(!mpu.begin(0x69)){
    Serial.println("failed to set up mpu6050");
  }






//  char message[64];
//  snprintf(message, 64, "%u Packets.", i++);
//  Wire.slaveWrite((uint8_t *)message, strlen(message));
  


  pinMode(T9, INPUT);
  pinMode(T8, INPUT);
  pinMode(T7, INPUT);
  pinMode(T6, INPUT);
  pinMode(T4, INPUT);

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G); //set accel range
  mpu.setGyroRange(MPU6050_RANGE_500_DEG); //set gyro range
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); //set filter bandwidth

}

void loop() {
  
}


void requestEvent() {
  Serial.println("event requested!");
  tum = digitalRead(T9);
  back = digitalRead(T8);
  leftCheek = digitalRead(T7);
  rightCheek = digitalRead(T6);
  head = digitalRead(T4);

  mpu.getEvent(&a, &g, &temp);

  doc["accX"] = a.acceleration.x;
  doc["accY"] = a.acceleration.y;
  doc["accZ"] = a.acceleration.z;
  doc["Tummy"] = !tum;
  doc["Back"] = !back;
  doc["Left Cheek"] = !leftCheek;
  doc["Right Cheek"] = !rightCheek;
  doc["Head"] = !head;
  serializeJson(doc, response, 128);
  Serial.println(response);
  Wire.write(response);
  
}


// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  Serial.println("event received!");
  while (Wire.available()) { // loop through all but the last
    c = Wire.read(); // receive byte as a character
    if (c) {
      Serial.print(c);
    }


  }
}
