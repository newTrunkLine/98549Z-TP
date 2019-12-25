#include "main.h"
#include "subsystemHeaders/drive.hpp"

// Helper Functions
void driveClass::setDrive(int left, int right)
{
  driveLeftFront = left;
  driveLeftBack = left;
  driveRightFront = right;
  driveRightBack = right;
}

// Driver Control Functions
void driveClass::setDriveOP()
{
  int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

  // Ignore joystick input if it's too small
  const int joystickDeadzone = 10;
  if(abs(leftJoystick) < joystickDeadzone){
    leftJoystick = 0;
  }
  if(abs(rightJoystick) < joystickDeadzone){
    rightJoystick = 0;
  }

  setDrive(leftJoystick, rightJoystick);
}
