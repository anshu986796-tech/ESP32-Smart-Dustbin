#include <ESP32Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const int handTrig = 5;
const int handEcho = 18;

const int garbageTrig = 17;
const int garbageEcho = 16;

const int servoPin = 13;
Servo lid;
LiquidCrystal_I2C lcd(0x27, 16, 2);
const float OPEN_DISTANCE = 20.0;
const float BIN_HEIGHT_CM = 30.0;

const int CLOSED_ANGLE = 0;
const int OPEN_ANGLE = 90;

unsigned long lastLcdUpdate = 0;
bool lidIsOpen = false;
float readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    return -1.0;
  }

  return duration * 0.0343 / 2.0;
}
void showGarbageLevel() {
  float distance = readDistance(garbageTrig, garbageEcho);

  lcd.setCursor(0, 0);

  if (distance < 0) {
    lcd.print("Garbage: No data");
    lcd.setCursor(0, 1);
    lcd.print("Check Sensor    ");
    Serial.println("Garbage sensor: NO ECHO");
    return;
  }
  float percentage =
      ((BIN_HEIGHT_CM - distance) / BIN_HEIGHT_CM) * 100.0;

  percentage = constrain(percentage, 0.0, 100.0);

  lcd.print("Garbage Level   ");
  lcd.setCursor(0, 1);
  lcd.print("Filled: ");
  lcd.print((int)percentage);
  lcd.print("%      ");

  Serial.print("Garbage distance: ");
  Serial.print(distance);
  Serial.print(" cm | Level: ");
  Serial.print(percentage);
  Serial.println("%");
}
void setup() {
  Serial.begin(115200);

  pinMode(handTrig, OUTPUT);
  pinMode(handEcho, INPUT);

  pinMode(garbageTrig, OUTPUT);
  pinMode(garbageEcho, INPUT);

  Wire.begin(21, 22);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Dustbin");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");

  lid.setPeriodHertz(50);
  lid.attach(servoPin, 500, 2400);
  lid.write(CLOSED_ANGLE);

  delay(1000);
  lcd.clear();
}
void loop() {
  float handDistance = readDistance(handTrig, handEcho);
  delay(60);
  if (handDistance > 0 && handDistance <= OPEN_DISTANCE) {
    if (!lidIsOpen) {
      lid.write(OPEN_ANGLE);
      lidIsOpen = true;
      Serial.println("Hand detected - Lid OPEN");
    }
  } else {
    if (lidIsOpen) {
      lid.write(CLOSED_ANGLE);
      lidIsOpen = false;
      Serial.println("Hand away - Lid CLOSED");
    }
  }
  if (millis() - lastLcdUpdate >= 1000) {
    lastLcdUpdate = millis();
    showGarbageLevel();
  }

  delay(60);
}
