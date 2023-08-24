
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
  
  Wire.begin(follower_address, I2C_SDA, I2C_SCL, 100000);  // join i2c bus with address #8, and the right pins
  Wire.onReceive(receiveEvent); // what to do when we get a write
  Wire.onRequest(requestEvent); //what to do when we get a read





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

        String acceleration = String("Acc X: " + String(a.acceleration.x) + " acc Y: " + String(a.acceleration.y) + " acc Z: " + String(a.acceleration.z));
        String touch = String("Tummy: " + String(tum) + ", Back: " + String(back) + ", Left Cheek: " + String(leftCheek) + ", Right Cheek: " + String(rightCheek) + ", Head: " + String(head));
        String response = String(acceleration + '\n' + touch);
        Serial.println("loop");

        delay(200);

}


void requestEvent() {
  tum = digitalRead(T9);
  back = digitalRead(T8);
  leftCheek = digitalRead(T7);
  rightCheek = digitalRead(T6);
  head = digitalRead(T4);

  mpu.getEvent(&a, &g, &temp);

//  String acceleration = String("Acc X: " + String(a.acceleration.x) + " acc Y: " + String(a.acceleration.y) + " acc Z: " + String(a.acceleration.z));
//  String touch = String("Tummy: " + String(tum) + ", Back: " + String(back) + ", Left Cheek: " + String(leftCheek) + ", Right Cheek: " + String(rightCheek) + ", Head: " + String(head));
//  String response = String(acceleration + '\n' + touch);
//  response.toCharArray(resp, uint(128));

  doc["accX"] = a.acceleration.x;
  doc["accY"] = a.acceleration.y;
  doc["accZ"] = a.acceleration.z;
  doc["Tummy"] = tum;
  doc["Back"] = back;
  doc["Left Cheek"] = leftCheek;
  doc["Right Cheek"] = rightCheek;
  doc["Head"] = head;
  serializeJson(doc, response, 128);
  Serial.println(response);
  Wire.write(response);
  
}


// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    c = Wire.read(); // receive byte as a character
    if (c) {

      //      tum = touchRead(T9);
      //      back = touchRead(T8);
      //      leftCheek = touchRead(T7);
      //      rightCheek = touchRead(T6);
      //      head = touchRead(T4);
      //
      //      mpu.getEvent(&a, &g, &temp);

      //      Serial.print("Acceleration X: ");
      //      Serial.print(a.acceleration.x);
      //      Serial.print(", Y: ");
      //      Serial.print(a.acceleration.y);
      //      Serial.print(", Z: ");
      //      Serial.print(a.acceleration.z);
      //      Serial.println(" m/s^2");
      //
      //      Serial.print("Rotation X: ");
      //      Serial.print(g.gyro.x);
      //      Serial.print(", Y: ");
      //      Serial.print(g.gyro.y);
      //      Serial.print(", Z: ");
      //      Serial.print(g.gyro.z);
      //      Serial.println(" rad/s");
      //
      //      Serial.print("Tummy: ");
      //      Serial.print(tum);
      //      Serial.print(", Back: ");
      //      Serial.print(back);
      //      Serial.print(", Left Cheek: ");
      //      Serial.print(leftCheek);
      //      Serial.print(", Right Cheek");
      //      Serial.print(rightCheek);
      //      Serial.print(", Head: ");
      //      Serial.println(head);
    }


  }
}
