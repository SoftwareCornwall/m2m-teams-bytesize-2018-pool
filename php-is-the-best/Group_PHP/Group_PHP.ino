#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"

namespace  
{
  int challenge=2;
  const int Left_Motor_Speed = 127;
  const int Right_Motor_Speed = 180;
  const byte interrupt_pin_2 = 2;
  const byte interrupt_pin_3 = 3;

  auto speed = 200;

  // Instantiate the two motor objects, passing in the side of the robot the motor is on
  Motor left_motor{"left"};
  Motor right_motor{"right"};

  // Instantiate a sensor object
  Sensor sensor{};
}

void turn_right(){
  left_motor.stop();
  right_motor.stop();
  delay(300);
  left_motor.forward(Left_Motor_Speed); 
  right_motor.reverse(Right_Motor_Speed); 
  delay(1280);
  left_motor.stop();
  right_motor.stop();
}

void move_forward(int _time_){
  delay(_time_);
  left_motor.forward(255); 
  right_motor.forward(255);
}

void qauter_right_turn(int _time_) {
  delay(_time_);
  turn_right();
}

void qauter_left_turn(int _time_) {
  delay(_time_);
  turn_left();
}

void stop_robot(int _time_) {
  delay(_time_);
  left_motor.stop();
  right_motor.stop();
}

void turn_left(){
  left_motor.stop();
  right_motor.stop();
  delay(300);
  right_motor.forward(Right_Motor_Speed); 
  left_motor.reverse(Left_Motor_Speed); 
  delay(1060);
  left_motor.stop();
  right_motor.stop();
}

void setup()
{
  Serial.begin(115200);
  pinMode(interrupt_pin_2, INPUT_PULLUP);
  pinMode(interrupt_pin_3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_2), left_motor_pulse_interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_3), right_motor_pulse_interrupt, RISING);
}

void loop()
{  
  if (challenge == 0)
  {
    if (sensor.distance_down() < 18) {
      left_motor.forward(Left_Motor_Speed); 
      right_motor.forward(Right_Motor_Speed);
    } else {
      right_motor.stop();
      left_motor.stop();
      delay(500);
      int bob1_foir_the_luls = left_motor.get_pulse_count();
      while((left_motor.get_pulse_count()-bob1_foir_the_luls) < 60) {
        left_motor.reverse(Left_Motor_Speed); 
        right_motor.reverse(Right_Motor_Speed); 
      }
      left_motor.stop();
      right_motor.stop();
      while(true){}
    }
    delay(54);
  }
  if(challenge == 2)
  {  
    move_forward(2000);     // delay(2000); left_motor.forward(255); right_motor.forward(255);
    qauter_right_turn(2000);     // delay(2000); turn_right();
    
    move_forward(2000);     // delay(2000); left_motor.forward(255); right_motor.forward(255);
    move_forward(2000);     // delay(2000); left_motor.forward(255); right_motor.forward(255);
    qauter_left_turn(2000);      // delay(2000); turn_left();
    
    move_forward(2000);     // delay(2000); left_motor.forward(255); right_motor.forward(255);
    qauter_left_turn(2000); // delay(2000); turn_left();
    
    move_forward(2000);        // delay(2000); left_motor.forward(255); right_motor.forward(255);
    qauter_left_turn(2000);        // delay(2000); turn_left();
    
    move_forward(2000);      // delay(2000); left_motor.forward(255); right_motor.forward(255);
    move_forward(2000);        // delay(2000); left_motor.forward(255); right_motor.forward(255);
    qauter_right_turn(2000);     // delay(2000); turn_right();  
    
    move_forward(2000);  // delay(2000); left_motor.forward(255); right_motor.forward(255);
    stop_robot(2000);         // delay(2000); left_motor.stop(); right_motor.stop();
    qauter_right_turn(2000); 
     while(true){}
  }
  if(challenge == 1)
  { 
    left_motor.reverse(255); 
    right_motor.reverse(255);
    delay(1000);
    left_motor.forward(255); 
    right_motor.forward(255);
    delay(2000);
    left_motor.stop();
    right_motor.stop();
    while(true){}
  }
  /*if (right_motor.get_pulse_count() > left_motor.get_pulse_count()) {
    right_motor.forward(Right_Motor_Speed - 60);
  } else if (right_motor.get_pulse_count() > left_motor.get_pulse_count()) {
    left_motor.forward(Left_Motor_Speed - 60);
  } else {
    left_motor.forward(Left_Motor_Speed); 
    right_motor.forward(Right_Motor_Speed);
  }
  if((left_motor.get_pulse_count()) > 1074) {
    left_motor.stop();
    right_motor.stop();
    while(true){}
  }*/
  /*analogWrite(13, 255);
  delay(1000);
  analogWrite(13, 0);
  delay(1000);*/
}

void left_motor_pulse_interrupt()
{
  left_motor.inc_pulse();
}

void right_motor_pulse_interrupt()
{
  right_motor.inc_pulse();
}
