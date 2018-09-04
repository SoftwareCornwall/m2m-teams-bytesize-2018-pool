#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"

class Robot{
  public:
    Motor motor_left{"left"};
    Motor motor_right{"right"};
    int Left_Motor_Speed;
    int Right_Motor_Speed;
  
    Robot(int lms, int rms)
    {
      Left_Motor_Speed = lms;
      Right_Motor_Speed = rms; 
    }
    
    void move_right(int _time_)
    {
      delay(_time_);
      motor_left.stop();
      motor_right.stop();
      delay(300);
      motor_left.forward(Left_Motor_Speed); 
      motor_right.reverse(Right_Motor_Speed); 
      delay(1280);
      motor_left.stop();
      motor_right.stop();
    }
    
    void move_forward(int _time_, int l = 255, int r = 255)
    {
      delay(_time_);
      motor_left.forward(l); 
      motor_right.forward(r);
    }

    void move_backward(int _time_)
    {
      delay(_time_);
      motor_left.reverse(255); 
      motor_right.reverse(255);
    }
    
    void stop_robot(int _time_) 
    {
      delay(_time_);
      motor_left.stop();
      motor_right.stop();
    }
    
    void move_left(int _time_)
    {
      delay(_time_);
      motor_left.stop();
      motor_right.stop();
      delay(300);
      motor_right.forward(Right_Motor_Speed); 
      motor_left.reverse(Left_Motor_Speed); 
      delay(1060);
      motor_left.stop();
      motor_right.stop();  
    }
};

namespace  
{
  int challenge = 0;
  const int Left_Motor_Speed = 127;
  const int Right_Motor_Speed = 180;
  const byte interrupt_pin_2 = 2;
  const byte interrupt_pin_3 = 3;

  auto speed = 200;

  // Instantiate the two motor objects, passing in the side of the robot the motor is o
  // Instantiate a sensor object
  Sensor sensor{};

  Motor left_motor{"left"};
  Motor right_motor{"right"};

  Robot robot(127, 180);
}

void setup()
{
  // movement::robot(127, 180);
  // 127 is the left moter speed
  Serial.begin(115200);
  pinMode(interrupt_pin_2, INPUT_PULLUP);
  pinMode(interrupt_pin_3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_2), left_motor_pulse_interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_3), right_motor_pulse_interrupt, RISING);
}

void loop()
{  
  int compliet = 1;
  if (challenge == 0) // checks whitch challenge we what to run
  {
    while(compliet)
    {
      delay(54);
      if (sensor.distance_down() < 12)
      {
        robot.move_forward(0,100,100);
      } 
      else 
      {
        robot.stop_robot(500);
        int bob1_foir_the_luls = left_motor.get_pulse_count();
        while((left_motor.get_pulse_count()-bob1_foir_the_luls) < 60) 
        {
          robot.move_backward(0);
          Serial.println("sg");
        }
        Serial.println("sg1");
        robot.move_left(2000);
        robot.move_left(2000);
        Serial.println("sg2");
        compliet = 0;
      }
    }
  }
  if(challenge == 2)
  {  
    robot.move_forward(2000);     // delay(2000); left_motor.forward(255); right_motor.forward(255);
    robot.move_right(2000);     // delay(2000); move_right();
    
    robot.move_forward(2000);     // delay(2000); left_motor.forward(255); right_motor.forward(255);
    robot.move_forward(2000);     // delay(2000); left_motor.forward(255); right_motor.forward(255);
    robot.move_right(2000);      // delay(2000); turn_left();
    
    robot.move_forward(2000);     // delay(2000); left_motor.forward(255); right_motor.forward(255);
    robot.move_right(2000); // delay(2000); turn_left();
    
    robot.move_forward(2000);        // delay(2000); left_motor.forward(255); right_motor.forward(255);
    robot.move_right(2000);        // delay(2000); turn_left();
    
    robot.move_forward(2000);      // delay(2000); left_motor.forward(255); right_motor.forward(255);
    robot.move_forward(2000);        // delay(2000); left_motor.forward(255); right_motor.forward(255);
    robot.move_right(2000);     // delay(2000); turn_right();  
    
    robot.move_forward(2000);  // delay(2000); left_motor.forward(255); right_motor.forward(255);
    robot.stop_robot(2000);         // delay(2000); left_motor.stop(); right_motor.stop();
    robot.move_right(2000); 
     while(true){}
  }
  
  if(challenge == 1)
  { 
    for (int b; b < 5; b++) {// loops through 4 times 
      robot.move_right(2000);// move right
      robot.move_forward(2000);// move farward
    }
  }
    /*robot.move_backward(255);
    delay(1000);
    robot.move_forward(255);
    delay(2000);
    left_motor.stop();
    right_motor.stop();
    while(true){}*/
  /*analogWrite(13, 255);
  delay(1000);
  analogWrite(13, 0);
  delay(1000);*/
  challenge++;
}

 void left_motor_pulse_interrupt()
{
  left_motor.inc_pulse();
}

void right_motor_pulse_interrupt()
{
  right_motor.inc_pulse();
}
