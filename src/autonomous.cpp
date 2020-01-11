#include "main.h"
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

// As I no longer have my TP robot, the values I use in auton are completely arbitrary

void blueFlags()
{
  // Toggles three flags

  // Move towards cap while intaking
  drivebase.autoMove(300, 127);
  balls.setIntakePower(127);
  pros::delay(500);
  // Move back to wall, stop intaking
  drivebase.autoMove(-300, 127);
  balls.setIntakePower(0);
  pros::delay(500);
  // Move forward a bit and turn towards flags
  drivebase.autoMove(50, 127);
  drivebase.autoRotate(90, 127);
  // Shoot top flag
  balls.setFlywheelPower(127);
  pros::delay(250);
  balls.setIntakePower(127);
  pros::delay(100);
  balls.setIntakePower(0);
  balls.setFlywheelPower(0);
  // Move forwards and shoot middle flag
  drivebase.autoMove(150, 127);
  balls.setFlywheelPower(127);
  pros::delay(250);
  balls.setIntakePower(127);
  pros::delay(100);
  balls.setIntakePower(0);
  balls.setFlywheelPower(0);
  // Move forward to toggle bottom flag
  drivebase.autoMove(200, 127);
}

void redFlags()
{
  // Toggles three flags

  // Move towards cap while intaking
  drivebase.autoMove(300, 127);
  balls.setIntakePower(127);
  pros::delay(500);
  // Move back to wall, stop intaking
  drivebase.autoMove(-300, 127);
  balls.setIntakePower(0);
  pros::delay(500);
  // Move forward a bit and turn towards flags
  drivebase.autoMove(50, 127);
  drivebase.autoRotate(-90, 127);
  // Shoot top flag
  balls.setFlywheelPower(127);
  pros::delay(250);
  balls.setIntakePower(127);
  pros::delay(100);
  balls.setIntakePower(0);
  balls.setFlywheelPower(0);
  // Move forwards and shoot middle flag
  drivebase.autoMove(150, 127);
  balls.setFlywheelPower(127);
  pros::delay(250);
  balls.setIntakePower(127);
  pros::delay(100);
  balls.setIntakePower(0);
  balls.setFlywheelPower(0);
  // Move forward to toggle bottom flag
  drivebase.autoMove(200, 127);
}

void blueCaps(bool isParked){}

void redCaps(bool isParked){}

void autonomous()
{

}
