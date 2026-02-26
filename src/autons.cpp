#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;

///
// Constants
///
void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(19, 0.0, 100);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.2, 0.017, 19.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are
  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}

void red_right_descore() {
  // drive to 3 balls
  chassis.pid_odom_set(16_in, 80, true);
  chassis.pid_wait();
  // turn intake om
  intake(100);
  // turn to the balls
  chassis.pid_turn_set(33_deg, TURN_SPEED);
  chassis.pid_wait();
  // intake
  chassis.pid_odom_set(16_in, 35, false);
  chassis.pid_wait();

  chassis.pid_odom_set(-4_in, 60, true);
  chassis.pid_wait();
  chassis.pid_turn_set({-16, 55}, fwd,  TURN_SPEED);
  chassis.pid_wait();

  // score middle
  chassis.pid_odom_set({{-4.5_in, 39_in}, fwd, DRIVE_SPEED},
                       true);

  chassis.pid_wait_until(6_in);
  
  intake(-60);

  chassis.pid_wait();

 intake(-80);

  pros::delay(1000);
  intake(100);

    // drive to the loader
  chassis.pid_odom_set({{{30.5_in, 0_in}, rev, 80},},true);
  chassis.pid_wait();

  // engage loader tool
  loader_mech.set(true);

  // intake from loader
  chassis.pid_turn_set({31, -21}, fwd,  TURN_SPEED);
  chassis.pid_wait();
  intake(100);

  chassis.pid_drive_set(9.5_in, 70);
  chassis.pid_wait();

  pros::delay(390);

    // go to the long goal and score.
  chassis.pid_odom_set({{{33_in, 10_in}, rev, 90},
                        {{33_in, 21.5_in}, rev, 90},},true);
  chassis.pid_wait_until_index(0);
  //intake(0);
  loader_mech.set(false);
  chassis.pid_wait();
  score_high(120);
  pros::delay(1200);
  score_stop();
  chassis.pid_drive_set(9.5_in, 90);
  chassis.pid_wait();
  chassis.pid_turn_set(225_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-12_in, 95);
  chassis.pid_wait();
  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-15.5_in, 65);
  chassis.pid_wait();
  
}

void red_right() {
  // drive to 3 balls
  chassis.pid_odom_set(16_in, 80, true);
  chassis.pid_wait();
  // turn intake om
  intake(100);
  // turn to the balls
  chassis.pid_turn_set(33_deg, TURN_SPEED);
  chassis.pid_wait();
  // intake
  chassis.pid_odom_set(20_in, 50, true);
  chassis.pid_wait();

  // turn to long goal
  chassis.pid_turn_set(65_deg, TURN_SPEED);//37
  chassis.pid_wait();

  // take ball under red goal
  chassis.pid_odom_set(15_in, 90, true);
  chassis.pid_wait();

  // drive to the middle goal
  chassis.pid_odom_set({{1_in, 34_in}, rev, 90},
                       true);
  chassis.pid_wait();
  intake(0);

  chassis.pid_turn_set({-16, 53}, fwd,  TURN_SPEED);
  chassis.pid_wait();

  intake(-60);
  // score middle
  chassis.pid_odom_set({{-7_in, 40_in}, fwd, 80},
                       true);
  chassis.pid_wait();
  intake(-80);

  pros::delay(800);
  intake(100);

  // drive to the loader
  chassis.pid_odom_set({{{30_in, 0_in}, rev, 80},},true);
  chassis.pid_wait();

  // engage loader tool
  loader_mech.set(true);

  // intake from loader
  chassis.pid_turn_set({30, -21}, fwd,  TURN_SPEED);
  chassis.pid_wait();
  intake(100);

  chassis.pid_drive_set(8_in, 60);
  chassis.pid_wait();

  pros::delay(380);

  intake(0);

  // go to the long goal and score.
  chassis.pid_odom_set({{{33_in, 10_in}, rev, 70},
                        {{33_in, 21.5_in}, rev, 70},},true);
  chassis.pid_wait_until_index(0);
  loader_mech.set(false);
  intake(100);
  chassis.pid_wait();
  score_high(100);
  pros::delay(2000);
}


void red_left_descore() {
  chassis.odom_x_flip();
  chassis.odom_theta_flip();
  // drive to 3 balls
  chassis.pid_odom_set(16_in, 80, true);
  chassis.pid_wait();
  // turn intake om
  intake(100);
  // turn to the balls
  chassis.pid_turn_set(33_deg, TURN_SPEED);
  chassis.pid_wait();
  // intake
  chassis.pid_odom_set(16_in, 35, true);
  chassis.pid_wait();

  // drive to the middle goal
  chassis.pid_odom_set(-4_in, 50, true);
  chassis.pid_wait();

  chassis.pid_turn_set({-7, 39}, rev,  TURN_SPEED);
  chassis.pid_wait();
  
  chassis.pid_odom_set({{{-7_in, 39_in}, rev, 80},},true);
  chassis.pid_wait();


  intake(0);
  // score middle
  score_low(100);
  pros::delay(100);
  outtake_piston.set(true);
  pros::delay(1100);
  score_stop();
  outtake_piston.set(false);

  // drive to loader
  chassis.pid_odom_set({{28.5_in, 2_in}, fwd, 80},
                       true);
  chassis.pid_wait();

    // engage loader tool
  loader_mech.set(true);
  pros::delay(50);

  chassis.pid_turn_set({30, -21}, fwd,  TURN_SPEED);
  chassis.pid_wait();

    // intake from loader
  intake(100);
  chassis.pid_odom_set(10_in, 90, true);
  chassis.pid_wait();
  
  pros::delay(350);

  intake(0);

  chassis.pid_odom_set({{{29_in, 10_in}, rev, 90},
                        {{29_in, 22.5_in}, rev, 90},},true);

  chassis.pid_wait_until_index(0);
  intake(100);
  loader_mech.set(false);
  chassis.pid_wait();
  score_high(120);
  pros::delay(1200);
  score_stop();
  chassis.pid_drive_set(9.7_in, 90);
  chassis.pid_wait();
  chassis.pid_turn_set(135_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-13_in, 95);
  chassis.pid_wait();
  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-15.5_in, 65);
  chassis.pid_wait();
}

void red_left() {
  chassis.odom_x_flip();
  chassis.odom_theta_flip();
  // drive to 3 balls
  chassis.pid_odom_set(16_in, 80, true);
  chassis.pid_wait();
  // turn intake om
  intake(100);
  // turn to the balls
  chassis.pid_turn_set(33_deg, TURN_SPEED);
  chassis.pid_wait();
  // intake
  chassis.pid_odom_set(8_in, 50, true);
  chassis.pid_wait();

  // turn to long goal
  chassis.pid_turn_set(48_deg, TURN_SPEED);
  chassis.pid_wait();

  // take ball under red goal
  chassis.pid_odom_set(25.5_in, 90, true);
  chassis.pid_wait();

  // drive to the middle goal
  chassis.pid_odom_set({{2_in, 33_in}, rev, 90},
                       true);
  chassis.pid_wait();
  intake(0);

  chassis.pid_turn_set({-17, 47}, rev,  TURN_SPEED);
  chassis.pid_wait();

    // score middle
  chassis.pid_odom_set({{-6_in, 38.5_in}, rev, 80},
                       true);
  chassis.pid_wait();

  
  score_low(100);
  pros::delay(100);
  outtake_piston.set(true);
  pros::delay(800);
  score_stop();
  outtake_piston.set(false);

  // drive to loader
  chassis.pid_odom_set({{29.5_in, 2_in}, fwd, 80},
                       true);
  chassis.pid_wait();

  // engage loader tool
  loader_mech.set(true);
  pros::delay(50);

  chassis.pid_turn_set({30, -21}, fwd,  TURN_SPEED);
  chassis.pid_wait();

  // intake from loader
  intake(100);
  chassis.pid_odom_set(11_in, 90, true);
  chassis.pid_wait();
  

  pros::delay(290);

  intake(0);
 
    // go to the long goal and score.
  chassis.pid_odom_set({{{30_in, 10_in}, rev, 70},
                        {{30_in, 21_in}, rev, 70},},true);
  chassis.pid_wait_until_index(0);
  loader_mech.set(false);
  chassis.pid_wait();
  pros::delay(50);
  score_high(100);
  pros::delay(2000);
}

void skills()
{
  const int DRIVESPEED =  70;
  const int TURNSPEED = 80;

  // open loader and go to the first loader
  loader_mech.set(true);
  descorer_right.set(true);

  chassis.pid_odom_set(31.5_in, DRIVESPEED, true);
  chassis.pid_wait();
    
  pros::delay(20);

  chassis.pid_turn_set(90_deg, TURNSPEED);
  chassis.pid_wait();

  // enable intake and get everything from the loader
  intake(100);
  pros::delay(50);
  chassis.pid_odom_set(10_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_odom_set(-1.5_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(50);
  chassis.pid_odom_set(3.5_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_odom_set(-1.5_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(50);
  chassis.pid_odom_set(3.5_in, DRIVESPEED, true);
  chassis.pid_wait();

  //pros::delay(200);


  // drive backwards, turn and go parallel to the goal
  chassis.pid_odom_set(-10_in, DRIVESPEED, true);
  chassis.pid_wait();
    
  pros::delay(20);

  chassis.pid_turn_set(135_deg, TURNSPEED);
  chassis.pid_wait();
  intake(0);
  loader_mech.set(false);

  pros::delay(20);

  chassis.pid_odom_set(-17.5_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(20);
  chassis.pid_turn_set(90_deg, TURNSPEED);
  chassis.pid_wait();
  pros::delay(20);
  chassis.pid_odom_set(-69_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(20);
  // turn and approach the goal
  chassis.pid_turn_set(0_deg, TURNSPEED);
  chassis.pid_wait();
  pros::delay(20);
  chassis.pid_odom_set(-11_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(20);
  chassis.pid_turn_set(270_deg, TURNSPEED);
  chassis.pid_wait();
  pros::delay(20);
  chassis.pid_odom_set(-9_in, 127, false);
  chassis.pid_wait();
  chassis.pid_turn_set(270_deg, TURNSPEED);
  chassis.pid_wait();
  
  // score
  score_high(-50);
  pros::delay(100);
  score_high(100);
  pros::delay(1900);

  //score_stop();

  // reset odo X,Y
  pros::delay(20);
  chassis.odom_x_set(0);
  chassis.odom_y_set(0);

  pros::delay(100);

  
  // get second loader
  loader_mech.set(true);

  chassis.pid_odom_set({{{-20_in, -0.7_in}, fwd, 70},},
                        true);
  chassis.pid_wait_until(1_in);
  score_stop();
  chassis.pid_wait();


  chassis.pid_turn_set(270_deg, TURNSPEED);
  chassis.pid_wait();

  intake(100);

  chassis.pid_odom_set(8_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_odom_set(-1.5_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(50);
  chassis.pid_odom_set(3.5_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_odom_set(-1.5_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(50);
  chassis.pid_odom_set(3.5_in, DRIVESPEED, true);
  chassis.pid_wait();

  // go backwards and score
  chassis.pid_odom_set({{{0_in, 0_in}, rev, 110},},
                        false);
  chassis.pid_wait();

  score_high(-50);
  pros::delay(100);
  score_high(100);
  pros::delay(1800);

//  score_stop();
  
  pros::delay(40);
  chassis.pid_turn_set(270_deg, TURNSPEED);
  chassis.pid_wait();

  // try to get control bonus by pushing the balls
  chassis.pid_odom_set(4_in, 60, true);
  chassis.pid_wait_until(1_in);
  score_stop();
  chassis.pid_wait();
  


  pros::delay(20);
  chassis.pid_odom_set(-6_in, 70, true);
  chassis.pid_wait();

  pros::delay(100);

  // reset odo, drive away from left goal, turn left
  chassis.odom_x_set(0);
  chassis.odom_y_set(0);
  pros::delay(100);

  chassis.pid_odom_set(8_in, DRIVESPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(180_deg, 60);
  chassis.pid_wait();

  // drive between long goals
  //chassis.pid_odom_set(96.5_in, DRIVESPEED, true);
  //chassis.pid_wait();
  
  chassis.pid_odom_set({{{-8_in, -96.75_in}, fwd, DRIVESPEED},},
                        true);
  chassis.pid_wait();


  chassis.pid_turn_set(270_deg, TURNSPEED);
  chassis.pid_wait();
 // loader_mech.set(true);

 // drive to goal, position using aligner tool
  chassis.pid_odom_set(-9_in, 110, false);
  chassis.pid_wait();

  // reset odo
  chassis.odom_x_set(0);
  chassis.odom_y_set(0);
  pros::delay(100);

  // go to the third loader and take everything it has!
  chassis.pid_odom_set({{{-20_in, 0.7_in}, fwd, 70},},
                        true);
  chassis.pid_wait();

  chassis.pid_turn_set(270_deg, TURNSPEED);
  chassis.pid_wait();

  intake(100);

  chassis.pid_odom_set(8_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_odom_set(-1.5_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(50);
  chassis.pid_odom_set(3.5_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_odom_set(-1.5_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(50);
  chassis.pid_odom_set(3.5_in, DRIVESPEED, true);
  chassis.pid_wait();

  // drive away from the loader
  chassis.pid_odom_set(-10_in, DRIVESPEED, true);
  chassis.pid_wait();

  // turn to the wall (backwards)
  chassis.pid_turn_set(315_deg, TURNSPEED);
  chassis.pid_wait();
  intake(0);
  loader_mech.set(false);

  // drive to the wall
  chassis.pid_odom_set(-17_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(20);

  // turn to drive parallel to the goal
  chassis.pid_turn_set(270_deg, TURNSPEED);
  chassis.pid_wait();
  pros::delay(20);

  // drive behind the right goal
  chassis.pid_odom_set(-69_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(20);

  // turn, drive back
  chassis.pid_turn_set(180_deg, TURNSPEED);
  chassis.pid_wait();
  pros::delay(20);

  chassis.pid_odom_set(-10.5_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(20);

  // turn backwards to the goal
  chassis.pid_turn_set(90_deg, TURNSPEED);
  chassis.pid_wait();
  pros::delay(20);
  // align and score
  chassis.pid_odom_set(-10.5_in, 127, false);
  chassis.pid_wait();
  chassis.pid_turn_set(90_deg, TURNSPEED);
  chassis.pid_wait();
  
  score_high(-50);
  pros::delay(100);
  score_high(100);
  pros::delay(1800);

  // reset odo
  chassis.odom_x_set(0);
  chassis.odom_y_set(0);
  pros::delay(100);

  loader_mech.set(true);

  // go to the loader
  chassis.pid_odom_set({{{20_in, 0.7_in}, fwd, 70},},
                        true);
  chassis.pid_wait_until(1_in);
    score_stop();
  chassis.pid_wait();


  chassis.pid_turn_set(90_deg, TURNSPEED);
  chassis.pid_wait();

  intake(100);

  chassis.pid_odom_set(8_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_odom_set(-1.5_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(50);
  chassis.pid_odom_set(3.5_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_odom_set(-1.5_in, DRIVESPEED, true);
  chassis.pid_wait();
  pros::delay(50);
  chassis.pid_odom_set(3.5_in, DRIVESPEED, true);
  chassis.pid_wait();

  // go back to the goal and score
  chassis.pid_odom_set({{{0_in, 0_in}, rev, 110},},
                        false);
  chassis.pid_wait();

  score_high(-50);
  pros::delay(100);
  score_high(100);
  pros::delay(1800);

  // try to get control bonus by pushing the balls
  chassis.pid_odom_set(4_in, 60, true);
  chassis.pid_wait_until(1_in);
  score_stop();
  chassis.pid_wait();
  pros::delay(20);
  loader_mech.set(false);
  chassis.pid_odom_set(-6_in, 70, true);
  chassis.pid_wait();

  pros::delay(100);


  // reset odo
  chassis.odom_x_set(0);
  chassis.odom_y_set(0);
  pros::delay(100);
  
  chassis.pid_odom_set(7_in, DRIVESPEED, true);
  chassis.pid_wait();
    chassis.pid_turn_set(45_deg, TURNSPEED);
  chassis.pid_wait();
    chassis.pid_odom_set(39_in, DRIVESPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(15_deg, TURNSPEED);
  chassis.pid_wait();
  loader_mech.set(true);  
  intake(100);  
  chassis.pid_odom_set(16_in, 110, false);
  chassis.pid_wait_until(4_in);
  loader_mech.set(false);  
  chassis.pid_wait();
  score_high(100);
  chassis.pid_turn_set(30_deg, TURNSPEED);
  chassis.pid_wait();
  pros::delay(2000);
}


///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(24_in, 30, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Odom Drive PID
///
void odom_drive_example() {
  // This works the same as pid_drive_set, but it uses odom instead!
  // You can replace pid_drive_set with pid_odom_set and your robot will
  // have better error correction.

  chassis.pid_odom_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_odom_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Odom Pure Pursuit
///
void odom_pure_pursuit_example() {
  // Drive to 0, 30 and pass through 6, 10 and 0, 20 on the way, with slew
  chassis.pid_odom_set({{{10_in, 10_in}, fwd, 60},
                        {{10_in, 20_in}, fwd, 60},
                        {{10_in, 30_in}, fwd, 60}},
                       true);
  chassis.pid_wait();

  // Drive to 0, 0 backwards
  chassis.pid_odom_set({{0_in, 0_in}, rev, 60},
                       true);
  chassis.pid_wait();
}

///
// Odom Pure Pursuit Wait Until
///
void odom_pure_pursuit_wait_until_example() {
  chassis.pid_odom_set({{{0_in, 24_in}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait_until_index(1);  // Waits until the robot passes 12, 24
  // Intake.move(127);  // Set your intake to start moving once it passes through the second point in the index
  chassis.pid_wait();
  // Intake.move(0);  // Turn the intake off
}

///
// Odom Boomerang
///
void odom_boomerang_example() {
  chassis.pid_odom_set({{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                       true);
  chassis.pid_wait();

  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Odom Boomerang Injected Pure Pursuit
///
void odom_boomerang_injected_pure_pursuit_example() {
  chassis.pid_odom_set({{{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Calculate the offsets of your tracking wheels
///
void measure_offsets() {
  // Number of times to test
  int iterations = 10;

  // Our final offsets
  double l_offset = 0.0, r_offset = 0.0, b_offset = 0.0, f_offset = 0.0;

  // Reset all trackers if they exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->reset();
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->reset();
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->reset();
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->reset();
  
  for (int i = 0; i < iterations; i++) {
    // Reset pid targets and get ready for running an auton
    chassis.pid_targets_reset();
    chassis.drive_imu_reset();
    chassis.drive_sensor_reset();
    chassis.drive_brake_set(MOTOR_BRAKE_HOLD);
    chassis.odom_xyt_set(0_in, 0_in, 0_deg);
    double imu_start = chassis.odom_theta_get();
    
    double target = i % 2 == 0 ? 90 : 270;  // Switch the turn target every run from 270 to 90

    // Turn to target at half power
    chassis.pid_turn_set(target, 63, ez::raw);
    chassis.pid_wait();
    pros::delay(250);

    // Calculate delta in angle
    double t_delta = util::to_rad(fabs(util::wrap_angle(chassis.odom_theta_get() - imu_start)));

    // Calculate delta in sensor values that exist
    double l_delta = chassis.odom_tracker_left != nullptr ? chassis.odom_tracker_left->get() : 0.0;
    double r_delta = chassis.odom_tracker_right != nullptr ? chassis.odom_tracker_right->get() : 0.0;
    double b_delta = chassis.odom_tracker_back != nullptr ? chassis.odom_tracker_back->get() : 0.0;
    double f_delta = chassis.odom_tracker_front != nullptr ? chassis.odom_tracker_front->get() : 0.0;

    // Calculate the radius that the robot traveled
    l_offset += l_delta / t_delta;
    r_offset += r_delta / t_delta;
    b_offset += b_delta / t_delta;
    f_offset += f_delta / t_delta;
  }

  // Average all offsets
  l_offset /= iterations;
  r_offset /= iterations;
  b_offset /= iterations;
  f_offset /= iterations;

  // Set new offsets to trackers that exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->distance_to_center_set(l_offset);
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->distance_to_center_set(r_offset);
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->distance_to_center_set(b_offset);
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->distance_to_center_set(f_offset);
}

// . . .
// Make your own autonomous functions here!
// . . .