#include "main.h"

// Constants
const int JOYSTICK_DEADZONE = 10;

// Helper Functions
void Drivebase::setDrivePower(int left, int right)
{
  // Sets voltage of each drive motor
  driveLeftFront = left;
  driveLeftBack = left;
  driveRightFront = right;
  driveRightBack = right;
}

// Driver Control Functions
void Drivebase::driverControl()
{
  // Get joystick positions
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
