#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"

namespace 
{
  const byte interrupt_pin_2 = 2;
  const byte interrupt_pin_3 = 3;

  const auto speed = 220;

  // Instantiate the two motor objects, passing in the side of the robot the motor is on
  Motor left_motor{"left"};
  Motor right_motor{"right"};

  // Instantiate a sensor object
  Sensor sensor{};

   float speedMultiplier = 0; //Used in accelerating the rover

  
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
    Serial.println(sensor.distance_down());
    if(speedMultiplier < 1){
      speedMultiplier += 0.005;
      left_motor.forward(speed * 1.05 * speedMultiplier);
      right_motor.forward(speed * speedMultiplier);
      
      delay(10);
      Stop();
      delay(10);
    }else{
      speedMultiplier = 1;
      MoveForward();
      delay(2000);
      Stop();
      delay(1000);
      FigureOfEight();
      delay(20000);
      FigureOfEight();
      delay(5999999);
      
    }
    

    
    
}
    

void left_motor_pulse_interrupt()
{
  left_motor.inc_pulse();
}

void right_motor_pulse_interrupt()
{
  right_motor.inc_pulse();
}

//Moves forwards for a time based on the argument provided
void MoveForward(float moveTime){
    
    left_motor.forward(speed * speedMultiplier);
    
    right_motor.forward(speed * speedMultiplier);
    delay(moveTime);
    Stop();
    delay(800);
}

//Moves forwards until instructed otherwise
void MoveForward(){
  
    left_motor.forward(speed * 1.05);
    right_motor.forward(speed);
}

//Moves backwards for time based on the argument provided
void MoveBackward(float moveTime){
  
    left_motor.reverse(speed * 1.05);
    right_motor.reverse(speed);
    delay(moveTime);
    Stop();
    delay(800);
}

//moves backwards until instructed otherwise
void MoveBackward(){
  
    left_motor.reverse(speed * 1.05);
    right_motor.reverse(speed);
}

//turns left based on the turn argument provided
void TurnLeft(float turn){
  
    left_motor.reverse(speed  * 0.75);
    right_motor.forward(speed * 0.75);
    delay((turn * 3000) / 0.75);
    Stop();
    delay(800);
  
}

//turns right based on the turn argument provided
void TurnRight(float turn){
  
    left_motor.forward(speed * 0.75);
    right_motor.reverse(speed * 0.75);
    delay((turn * 2900) / 0.7);
    Stop();
    delay(800);
}

//turns right until told otherwise
void TurnRight(){
  
    left_motor.forward(speed * 0.75);
    right_motor.reverse(speed * 0.75);
}

//Stops both motors
void Stop(){
  left_motor.stop();
  right_motor.stop();
}



//Move forwards until detects obstacle then does a 360, moves backwards, then does a 180 turn 
void DemoMoonWalk(){
  if(sensor.distance_forwards() < 10){
      
      MoveBackward(500);  
      TurnRight(1.57);
      
      MoveBackward(1500);
      TurnRight(0.86);
      
      MoveForward(1500);
      
      delay(1000000);
    }else{
      MoveForward();
    }
    delay(50);
}

void FigureOfEight(){
  left_motor.forward((speed * 1.05)/2);
  right_motor.forward(speed/2);
  delay(4000);
  left_motor.forward((speed * 1.05));
  right_motor.forward(speed/6);
  delay(8500);
  
  left_motor.forward((speed * 1.05)/2);
  right_motor.forward(speed/2);
  delay(4000);
  left_motor.forward((speed * 1.05)/5);
  right_motor.forward(speed);
  delay(8500);
}


/* 



  (left_motor.get_pulse_count() = count {
  if(left_motor.get_pulse_count() < count + 502)
   left_motor.forward(movementSpeed - 4);

(right_motor.get_pulse_count() = count1 {
if(right_motor.get_pulse_count() < count1 + 502)
  right_motor.forward(movementSpeed);

*/


