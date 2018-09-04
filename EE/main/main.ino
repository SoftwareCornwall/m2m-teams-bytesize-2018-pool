#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"

namespace {
  const byte interrupt_pin_2 = 2;
  const byte interrupt_pin_3 = 3;

  auto speed = 200;
  int distance_forward_straight = 0;

  int left_motor_speed = 100;
  int right_motor_speed = 80;
  
  // Instantiate the two motor objects, passing in the side of the robot the motor is on
  Motor left_motor{"left"};
  Motor right_motor{"right"};

  // Instantiate a sensor object
  Sensor sensor{};
}

void setup() {
  Serial.begin(115200);
  pinMode(interrupt_pin_2, INPUT_PULLUP);
  pinMode(interrupt_pin_3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_2), left_motor_pulse_interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_3), right_motor_pulse_interrupt, RISING);
}


void loop() {  
    forward_adjustment(926);
}

void forward_adjustment(unsigned long distance) {
  if (left_motor.get_pulse_count() > distance || right_motor.get_pulse_count() > distance) {
    left_motor.stop();
    right_motor.stop();
    delay(100000);
  }
  else {
    left_motor.forward(left_motor_speed);
    right_motor.forward(right_motor_speed);
  }
}

void forward() {
  left_motor.forward(speed);
  right_motor.forward(speed);
}
  
void backward() {
  left_motor.reverse(speed);
  right_motor.reverse(speed);
}

void stop_motors() {
  left_motor.stop();
  right_motor.stop();
}


void left_motor_pulse_interrupt() {
  left_motor.inc_pulse();
}

void right_motor_pulse_interrupt() {
  right_motor.inc_pulse();
}
