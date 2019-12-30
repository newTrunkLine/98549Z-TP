#include "main.h"

// Constants
const int JOYSTICK_DEADZONE = 8;
const int MAX_VOLTAGE = 127;
const int MIN_VOLTAGE = -127;

// Helper Functions
void Drivebase::setDrivePower(int left, int right)
{
  // Sets voltage of each drive motor
  driveLeftFront = left;
  driveLeftBack = left;
  driveRightFront = right;
  driveRightBack = right;
}

int Drivebase::expoDrive(int joystickValue)
{
    int output = 0;
    // Ignore joystick input if it's too small
    if(abs(joystickValue) < JOYSTICK_DEADZONE){
      // Do nothing
    }
    else{
      // Direction is either 1 or -1, based on joystick value
      int direction = abs(joystickValue) / joystickValue;
      // Plug joystick value into exponential function, return result
      output = direction * (1.2 * pow(1.0356, abs(joystickValue)) - 1.2 + 0.2 * abs(joystickValue));
    }
    return output;
}

void Drivebase::resetDriveEncoders()
{
  driveLeftFront.tare_position();
  driveLeftBack.tare_position();
  driveRightFront.tare_position();
  driveRightBack.tare_position();
}

double Drivebase::getAveDriveEncoderValue()
{
  return (fabs(driveLeftFront.get_position())
        + fabs(driveLeftBack.get_position())
        + fabs(driveRightFront.get_position())
        + fabs(driveRightBack.get_position())) / 4;
}

// Driver Control Functions
void Drivebase::driverControlTank()
{
  // Basic double-joystick tank drive
  // Left joystick controls left side of drivebase and right joystick controls right side of drivebase

  // Get joystick values
  int leftJoystick = expoDrive(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
  int rightJoystick = expoDrive(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));

  setDrivePower(leftJoystick, rightJoystick);
}

void Drivebase::driverControlStrafe()
{
  // Experimental double-joystick arcade drive if we ever used mechanum wheels
  int forward = expoDrive(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
  int sideways = expoDrive(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X));
  int turn = expoDrive(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));

  driveLeftFront = forward + sideways + turn;
  driveLeftBack = forward - sideways + turn;
  driveRightFront = forward - sideways - turn;
  driveRightBack = forward + sideways - turn;
}

void Drivebase::driverControlArcade()
{
  // Split arcade drive, but with an added exponential function for adjustment accuracy
  // Left joystick controls forwards/backwards motion
  // Right joystick controls turning motion

  // Get joystick values
  int splitArcadeY = expoDrive(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
  int splitArcadeX = expoDrive(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));

  // Left = Left Y + Right X
  int left = splitArcadeY + splitArcadeX;

  // Right = Left Y - Right X
  int right = splitArcadeY - splitArcadeX;

  setDrivePower(left, right);
}

// Autonomous Functions
void Drivebase::movePD(int targetPosition, int timeout)
{
  // Proportional-Derivative drive for auton

  // Direction is either 1 or -1, based on target position
  int direction = abs(targetPosition) / targetPosition;

  // Variables
  float kP = 0.0;
  float kD = 0.0;
  int currentPosition = 0;
  int error = 0;
  int errorDiff = 0;
  int errorPrevious = 0;
  int power = 0;

  // Reset timer and motor encoders
  int startTime = pros::millis();
  resetDriveEncoders();

  while((pros::millis() - startTime) < timeout){
    currentPosition = getAveDriveEncoderValue();

    // PROPORTIONAL
    error = targetPosition - currentPosition;

    // DERIVATIVE
    errorDiff = error - errorPrevious;
    errorPrevious = error;

    // Power = P + D
    power = (error * kP) + (errorDiff * kD);

    // Cap power
    if(power > MAX_VOLTAGE){
      power = MAX_VOLTAGE;
    }
    if(power < MIN_VOLTAGE){
      power = MIN_VOLTAGE;
    }

    setDrivePower(power * direction, power * direction);

    pros::delay(20);
  }
}
