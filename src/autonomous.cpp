#include "main.h"

// As I no longer have either my TP robot or competition code, the values I use in auton are completely arbitrary

// =============================================================================
//                             Forward Declarations
// =============================================================================

void blueFlags(bool alliancePark);
void redFlags(bool alliancePark);
void blueCaps(bool alliancePark);
void redCaps(bool alliancePark);
void skills();

// =============================================================================
//                                  Autonomous
// =============================================================================

void autonomous()
{
  blueFlags(false);
}

// =============================================================================
//                                  Blue Flags
// =============================================================================

void blueFlags(bool alliancePark)
{
  // Move forward and push cap off ball
  drivebase.autoMove(300, 127);
  pros::delay(500);
  // Intake ball and move back to wall
  balls.setIntakePower(127);
  pros::delay(100);
  balls.setIntakePower(0);
  drivebase.autoMove(-300, 127);
  pros::delay(500);
  // Move forward and turn towards flags
  drivebase.autoMove(50, 127);
  drivebase.autoRotate(90, 127);
  // Shoot top flag
  balls.setFlywheelPower(127);
  pros::delay(250);
  balls.setIntakePower(127);
  pros::delay(100);
  balls.setIntakePower(0);
  balls.setFlywheelPower(0);
  // Move forward and shoot middle flag
  drivebase.autoMove(150, 127);
  balls.setFlywheelPower(127);
  pros::delay(250);
  balls.setIntakePower(127);
  pros::delay(100);
  balls.setIntakePower(0);
  balls.setFlywheelPower(0);
  // Move forward to hit bottom flag
  drivebase.autoRotate(10, 127);
  drivebase.autoMove(200, 127);

  if(alliancePark){
    // Move back and turn to face platforms
    drivebase.autoMove(-500, 127);
    drivebase.autoRotate(-90, 127);
    // Drive onto alliance platform
    drivebase.autoMove(200, 127);
  }
  else{
    // Move back and turn to face cap
    drivebase.autoMove(-200, 127);
    drivebase.autoRotate(-90, 127);
    // Move forward and outtake to flip cap
    drivebase.autoMove(200, 127);
    balls.setIntakePower(-127);
  }
}

// =============================================================================
//                                Red Flags
// =============================================================================

void redFlags(bool alliancePark)
{
  // Move forward and push cap off ball
  drivebase.autoMove(300, 127);
  pros::delay(500);
  // Intake ball and move back to wall
  balls.setIntakePower(127);
  pros::delay(100);
  balls.setIntakePower(0);
  drivebase.autoMove(-300, 127);
  pros::delay(500);
  // Move forward and turn towards flags
  drivebase.autoMove(50, 127);
  drivebase.autoRotate(-90, 127);
  // Shoot top flag
  balls.setFlywheelPower(127);
  pros::delay(250);
  balls.setIntakePower(127);
  pros::delay(100);
  balls.setIntakePower(0);
  balls.setFlywheelPower(0);
  // Move forward and shoot middle flag
  drivebase.autoMove(150, 127);
  balls.setFlywheelPower(127);
  pros::delay(250);
  balls.setIntakePower(127);
  pros::delay(100);
  balls.setIntakePower(0);
  balls.setFlywheelPower(0);
  // Move forward to hit bottom flag
  drivebase.autoRotate(-10, 127);
  drivebase.autoMove(200, 127);

  if(alliancePark){
    // Move back and turn to face platforms
    drivebase.autoMove(-500, 127);
    drivebase.autoRotate(90, 127);
    // Drive onto alliance platform
    drivebase.autoMove(200, 127);
  }
  else{
    // Move back and turn to face cap
    drivebase.autoMove(-200, 127);
    drivebase.autoRotate(90, 127);
    // Move forward and outtake to flip cap
    drivebase.autoMove(200, 127);
    balls.setIntakePower(-127);
  }
}

// =============================================================================
//                                  Blue Caps
// =============================================================================

void blueCaps(bool alliancePark)
{
  if(!alliancePark){
    // Shoot middle flag
    balls.setFlywheelPower(127);
    pros::delay(250);
    balls.setIntakePower(127);
    pros::delay(100);
    balls.setIntakePower(0);
    balls.setFlywheelPower(0);
    // Turn to face caps
    drivebase.autoRotate(-90, 127);
  }
  // Move forward and push cap off ball
  drivebase.autoMove(300, 127);
  pros::delay(500);
  // Move back and turn to face other cap
  drivebase.autoMove(-100, 127);
  pros::delay(100);
  drivebase.autoRotate(-45, 127);
  pros::delay(100);
  // Move forward while outtaking to flip cap
  drivebase.autoMove(150, 127);
  balls.setIntakePower(-127);
  pros::delay(200);
  if(alliancePark){
    // Move backward and turn to face alliance platform
    drivebase.autoMove(-150, 127);
    pros::delay(100);
    drivebase.autoRotate(135, 127);
    pros::delay(100);
    // Drive onto platform
    drivebase.autoMove(100, 127);
  }
}

// =============================================================================
//                                   Red Caps
// =============================================================================

void redCaps(bool alliancePark)
{
  if(!alliancePark){
    // Shoot middle flag
    balls.setFlywheelPower(127);
    pros::delay(250);
    balls.setIntakePower(127);
    pros::delay(100);
    balls.setIntakePower(0);
    balls.setFlywheelPower(0);
    // Turn to face caps
    drivebase.autoRotate(90, 127);
  }
  // Move forward and push cap off ball
  drivebase.autoMove(300, 127);
  pros::delay(500);
  // Move back and turn to face other cap
  drivebase.autoMove(-100, 127);
  pros::delay(100);
  drivebase.autoRotate(45, 127);
  pros::delay(100);
  // Move forward while outtaking to flip cap
  drivebase.autoMove(150, 127);
  balls.setIntakePower(-127);
  pros::delay(200);
  if(alliancePark){
    // Move backward and turn to face alliance platform
    drivebase.autoMove(-150, 127);
    pros::delay(100);
    drivebase.autoRotate(-135, 127);
    pros::delay(100);
    // Drive onto platform
    drivebase.autoMove(100, 127);
  }
}

// =============================================================================
//                                    Skills
// =============================================================================

void skills()
{
  // As much as I'd like to make a skills function, all the values would be arbitrary
  // and it's hard to guage what tasks my robot would be able to accomplish in the
  // time limit when I can't test my program
}
