# ESP32 Smart Dustbin

## About the Project
A Smart Dustbin simulation developed using ESP32 in Wokwi.

## Components Used
- ESP32 DevKit
- 2 HC-SR04 Ultrasonic Sensors
- SG90 Servo Motor
- 16x2 I2C LCD

## Features
- Automatic lid opening when a hand is detected.
- Automatic lid closing when the hand moves away.
- Garbage-level monitoring.
- Garbage percentage displayed on the LCD.

## Pin Connections
- Hand sensor: TRIG GPIO 5, ECHO GPIO 18
- Garbage sensor: TRIG GPIO 17, ECHO GPIO 16
- Servo signal: GPIO 13
- LCD SDA: GPIO 21, SCL: GPIO 22

## Simulation
Wokwi simulation project: [https://wokwi.com/projects/478668202561477633]

## Project Status
Wokwi simulation tested successfully. Physical hardware implementation is in progress.
