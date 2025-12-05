#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

inline bool toggle_intake=false;

inline pros::Motor motor_intake(10, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

inline pros::Motor motor_ramp(-9, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);


inline void intake(int speed)
{
  if(!toggle_intake){
   motor_intake.move(speed);
   motor_ramp.move(speed);
   toggle_intake = true;
  }
  else{
    motor_intake.move(0);
    motor_ramp.move(0);
    toggle_intake = false;
  }
}

// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');