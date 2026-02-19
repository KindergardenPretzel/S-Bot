#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

inline bool toggle_intake=false;
inline bool intake_positive = false;

inline bool toggle_low = false;

inline bool toggle_high = false;



inline pros::Motor motor_intake(10, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
inline pros::Motor motor_ramp(-9, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

inline Piston intake_piston ('C');
inline Piston gate_piston('D');
inline Piston outtake_piston('H');
inline Piston descorer_right('G');
inline Piston loader_mech('A');


inline void intake(int speed)
{

  if (speed > 0) {
    intake_piston.set(false);
    motor_intake.move(speed);
    motor_ramp.move(speed);
    intake_positive = true;
  }
  if (speed < 0) {
    intake_piston.set(true);
    motor_intake.move(speed);
    motor_ramp.move(speed);
    intake_positive = false;
  }
  if (speed == 0) {
    motor_intake.move(0);
    motor_ramp.move(0);
    intake_piston.set(false);
  }
  
}


inline void score_low(int speed)
{
  if (toggle_intake) {
    toggle_intake = false;
  }
   motor_intake.move(speed);
   motor_ramp.move(speed);
   toggle_low = true;
}

inline void score_high(int speed)
{
    if (toggle_intake) {
    toggle_intake = false;
  }
    gate_piston.set(true);
   motor_intake.move(speed);
   motor_ramp.move(speed);
   toggle_high = true;
}

inline void score_stop() {
    if (!toggle_intake) {
     motor_intake.move(0);
     motor_ramp.move(0);
    }
    toggle_high = false;
    toggle_low = false;
    gate_piston.set(false);


}


