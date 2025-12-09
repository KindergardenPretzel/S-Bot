#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

inline bool toggle_intake=false;

inline bool toggle_low = false;

inline pros::Motor motor_intake(10, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

inline pros::Motor motor_ramp(-9, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

inline pros::Motor motor_score(7, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

inline pros::ADIDigitalOut intake_piston (3, LOW);


inline void intake(int speed)
{
  if(!toggle_intake){
   motor_intake.move(speed);
   motor_ramp.move(speed);
   if(speed > 0)
   {
      intake_piston.set_value(LOW);
      motor_score.move(speed);
   }
   else
   {
      intake_piston.set_value(HIGH);
   }
   toggle_intake = true;
  }
  else{
    motor_intake.move(0);
    motor_ramp.move(0);
    motor_score.move(0);
    intake_piston.set_value(LOW);
    toggle_intake = false;
  }
}

inline void score_low(int speed)
{
  if(!toggle_low){
   motor_intake.move(-100);
   motor_ramp.move(-100);
   pros::delay(200);
   motor_intake.move(0);
   motor_ramp.move(0);

   motor_intake.move(speed);
   motor_ramp.move(speed);
   motor_score.move(-40);
   toggle_low = true;
  }
  else if(toggle_low){
    motor_intake.move(0);
    motor_ramp.move(0);
    motor_score.move(0);
    toggle_low = false;
  }
}

// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');