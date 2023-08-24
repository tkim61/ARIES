
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
//RPi:SCL/GPIO5 --> ESP32:TXD0/IO/GREEN
//IO17, IO26 are free for I2C, pins 28 and 10
//RPi:SDA/GPIO3 --> ESP32:RXD0/34

#include <ArduinoJson.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#define I2C_SDA 17
#define I2C_SCL 26


Adafruit_MPU6050 mpu;

const uint8_t follower_address = 0x08;
static_assert(LOW == 0, "Expecting LOW to be 0");

int tum, back, leftCheek, rightCheek, head;
sensors_event_t a, g, temp; //a is accel, g is gyro, in x, y , and z
char c;

StaticJsonDocument<128> doc;
char response[128];

void setup() {
  Serial.begin(115200);

  pinMode(T9, INPUT);
  pinMode(T8, INPUT);
  pinMode(T7, INPUT);
  pinMode(T6, INPUT);
  pinMode(T4, INPUT);

  if (!mpu.begin(0x69)) {
        Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }





  mpu.setAccelerometerRange(MPU6050_RANGE_8_G); //set accel range
  mpu.setGyroRange(MPU6050_RANGE_500_DEG); //set gyro range
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); //set filter bandwidth

}

void loop() {
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
        delay(200);

}
