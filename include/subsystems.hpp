#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

inline bool toggle_intake=false;

inline bool toggle_low = false;

inline bool toggle_high = false;

inline pros::Motor motor_intake(10, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

inline pros::Motor motor_ramp(-9, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

//inline pros::Motor motor_score(7, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

inline pros::ADIDigitalOut intake_piston ('C', LOW);
inline pros::ADIDigitalOut gate_piston ('D', LOW);

inline pros::ADIDigitalOut outtake ('H', LOW);
inline pros::ADIDigitalOut descorer_right ('G', LOW);

inline pros::ADIDigitalOut loader_mech ('A', LOW);

inline void intake(int speed)
{
  if(!toggle_intake){
   motor_intake.move(speed);
   motor_ramp.move(speed);
   if(speed > 0)
   {
      intake_piston.set_value(LOW);
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
    intake_piston.set_value(LOW);
    toggle_intake = false;
  }
}


inline void score_low(int speed)
{
  if (toggle_intake) {
    toggle_intake = false;
  }
//  if(!toggle_low){
   motor_intake.move(speed);
   motor_ramp.move(speed);
   outtake.set_value(HIGH);
   toggle_low = true;
//  }
//  else if(toggle_low){
//    motor_intake.move(0);
//    motor_ramp.move(0);
//    motor_score.move(0);
//    toggle_low = false;
//  }
}

inline void score_high(int speed)
{
    if (toggle_intake) {
    toggle_intake = false;
  }
 // if(!toggle_high){
   motor_intake.move(speed);
   motor_ramp.move(speed);
   gate_piston.set_value(HIGH);
   toggle_high = true;
 // }
 // else if(toggle_high){
 //   motor_intake.move(0);
 //   motor_ramp.move(0);
 //   motor_score.move(0);
 //   gate_piston.set_value(LOW);
 //   toggle_high = false;
 // }
}

inline void score_stop() {
    if (!toggle_intake) {
     motor_intake.move(0);
     motor_ramp.move(0);
    }
    toggle_high = false;
    toggle_low = false;
    gate_piston.set_value(LOW);
    outtake.set_value(LOW);
}

inline void descorer_on() {
  static bool descorer_toggle = false;
  if (!descorer_toggle) {
    descorer_right.set_value(true);
    descorer_toggle = true;
  }
  else {
    descorer_right.set_value(false);
    descorer_toggle = false;
  }

}

inline void loader() {
  static bool loader_toggle = false;
  if (!loader_toggle) {
    loader_mech.set_value(HIGH);
    loader_toggle = true;
  }
  else {
    loader_mech.set_value(LOW);
    loader_toggle = false;
  }

}
// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');