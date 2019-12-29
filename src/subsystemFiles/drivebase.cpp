#include "main.h"

// Constants
const int JOYSTICK_DEADZONE = 8;

// Helper Functions
void Drivebase::setDrivePower(int left, int right)
{
  // Sets voltage of each drive motor
  driveLeftFront = left;
  driveLeftBack = left;
  driveRightFront = right;
  driveRightBack = right;
}

int Drivebase::expoFunction(int joystickValue)
{
    // Direction is either 1 or -1, based on joystick value
    int direction = abs(joystickValue) / joystickValue;
    // Plug joystick value into exponential function, return result
    int output = direction * (1.2 * pow(1.0356, abs(joystickValue)) - 1.2 + 0.2 * abs(joystickValue));
    return output;
}

// Driver Control Functions
void Drivebase::driverControlTank()
{
  // Basic double-joystick tank drive
  // Left joystick controls left side of drivebase and right joystick controls right side of drivebase

  // Get joystick values
  int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

  // Ignore joystick input if it's too small
  if(abs(leftJoystick) < JOYSTICK_DEADZONE){
    leftJoystick = 0;
  }
  if(abs(rightJoystick) < JOYSTICK_DEADZONE){
    rightJoystick = 0;
  }

  setDrivePower(leftJoystick, rightJoystick);
}

void Drivebase::driverControlSplitArcade()
{
  // Double-joystick split arcade drive
  // Left joystick controls forwards/backwards motion
  // Right joystick controls turning motion

  // Get joystick values
  int splitArcadeY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int splitArcadeX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

  // Ignore joystick input if it's too small
  if(abs(splitArcadeY) < JOYSTICK_DEADZONE){
    splitArcadeY = 0;
  }
  if(abs(splitArcadeX) < JOYSTICK_DEADZONE){
    splitArcadeX = 0;
  }

  // Left = left Y + right X
  int left = splitArcadeY + splitArcadeX;

  // Right = left Y - right X
  int right = splitArcadeY - splitArcadeX;

  setDrivePower(left, right);
}

void Drivebase::driverControlExpo()
{
  // Same controls as split arcade drive, but now with an added exponential function for adjustment accuracy

  // Get joystick values
  int splitArcadeY = expoFunction(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
  int splitArcadeX = expoFunction(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));

  // Ignore joystick input if it's too small
  if(abs(splitArcadeY) < JOYSTICK_DEADZONE){
    splitArcadeY = 0;
  }
  if(abs(splitArcadeX) < JOYSTICK_DEADZONE){
    splitArcadeX = 0;
  }

  // Left = left Y + right X
  int left = splitArcadeY + splitArcadeX;

  // Right = left Y - right X
  int right = splitArcadeY - splitArcadeX;

  setDrivePower(left, right);
}

// Autonomous Functions
