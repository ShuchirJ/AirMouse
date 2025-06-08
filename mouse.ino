#include <Adafruit_LSM6DSOX.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <BleMouse.h>

BleMouse bleMouse("The Wand");
Adafruit_LSM6DSOX sox;
int BUTTON_LEFT = 3;
int BUTTON_RIGHT = 4;

bool prevLeft = false;
bool prevRight = false;

void setup(void) {
  Serial.begin(115200);
  
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);

  initalize
  if (!sox.begin_I2C()) {
    Serial.println("Failed to init accel.");
    while (1) {
      delay(10);
    }
  }
  Serial.println("accel. initialized");

  sox.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);
  sox.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS);
  sox.setAccelDataRate(LSM6DS_RATE_104_HZ);
  sox.setGyroDataRate(LSM6DS_RATE_104_HZ);

  bleMouse.begin();
}

void loop() {
  sensors_event_t a, g, temp;
  sox.getEvent(&a, &g, &temp);

  if (bleMouse.isConnected()) {
    sensors_event_t a, g, temp;
    sox.getEvent(&a, &g, &temp);

    int moveX = a.acceleration.x * 2; 
    int moveY = a.acceleration.y * 2; 

    int scroll = g.gyro.y * 2;

    if (abs(moveX) < 1) moveX = 0;
    if (abs(moveY) < 1) moveY = 0;
    if (abs(scroll) < 0.5) scroll = 0;

    if (moveX != 0 || moveY != 0) {
      bleMouse.move(moveX, moveY);
    }

    if (scroll != 0) {
      bleMouse.move(0, 0, scroll);
    }

    bool leftPressed = digitalRead(BUTTON_LEFT) == LOW;
    bool rightPressed = digitalRead(BUTTON_RIGHT) == LOW;

    if (leftPressed && !prevLeft) {
      Serial.println("press left");
      bleMouse.press(MOUSE_LEFT);
      prevLeft = true;
    } else if (!leftPressed && prevLeft) {
      Serial.println("release left");
      bleMouse.release(MOUSE_LEFT);
      prevLeft = false;
    }

    if (rightPressed && !prevRight) {
      Serial.println("press right");
      bleMouse.press(MOUSE_RIGHT);
      prevRight = true;
    } else if (!rightPressed && prevRight) {
      Serial.println("release right");
      bleMouse.release(MOUSE_RIGHT);
      prevRight = false;
    }
  }

  delay(20);
}