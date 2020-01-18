#include "main.h"

// =============================================================================
//                            Initialize Variables
// =============================================================================

Drivebase::Drivebase()
{
  kP = 0.0;
  kD = 0.0;
}

// =============================================================================
//                              Helper Functions
// =============================================================================

void Drivebase::setDrivePower(int left, int right)
{
  // Sets voltage of each drive motor
  driveLeftFront = left;
  driveLeftBack = left;
  driveRightFront = right;
  driveRightBack = right;
}

void Drivebase::resetDriveSensors(bool resetGyro)
{
  driveLeftFront.tare_position();
  driveLeftBack.tare_position();
  driveRightFront.tare_position();
  driveRightBack.tare_position();
  if(resetGyro){
    gyro.reset();
  }
}

double Drivebase::getAveDriveEncoderValue()
{
  return (fabs(driveLeftFront.get_position())
        + fabs(driveLeftBack.get_position())
        + fabs(driveRightFront.get_position())
        + fabs(driveRightBack.get_position())) / 4;
}

int Drivebase::getExpoValue(int joystickValue)
{
    output = 0;
    // Ignore joystick input if it's too small
    if(abs(joystickValue) > JOYSTICK_DEADZONE){
      // Direction is either 1 or -1, based on joystick value
      direction = abs(joystickValue) / joystickValue;
      // Plug joystick value into exponential function, return result
      output = direction * (1.2 * pow(1.0356, abs(joystickValue)) - 1.2 + 0.2 * abs(joystickValue));
    }
    return output;
}

// =============================================================================
//                          Driver Control Functions
// =============================================================================

void Drivebase::driverControlTank()
{
  // Left joystick controls left side of drivebase
  // Right joystick controls right side of drivebase

  // Get joystick values
  leftPower = getExpoValue(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
  rightPower = getExpoValue(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
  setDrivePower(leftPower, rightPower);
}

void Drivebase::driverControlArcade()
{
  // Left joystick controls forwards/backwards motion
  // Right joystick controls turning motion

  // Get joystick values
  arcadeY = getExpoValue(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
  arcadeX = getExpoValue(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));

  leftPower = arcadeY + arcadeX;
  rightPower = arcadeY - arcadeX;

  setDrivePower(leftPower, rightPower);
}

// =============================================================================
//                            Autonomous Functions
// =============================================================================

void Drivebase::autoMove(int targetValue, int voltage)
{
  // Drive function from 4411S's PROS tutorials

  // Direction is either 1 or -1, based on target value
  direction = abs(targetValue) / targetValue;
  // Reset motor encoders and gyro
  resetDriveSensors(true);

  while(getAveDriveEncoderValue() < abs(targetValue)){
    // Use gyro value to correct deviations
    setDrivePower(voltage * direction + gyro.get_value(), voltage * direction - gyro.get_value());
    pros::delay(10);
  }
  // Brief break
  setDrivePower(-10 * direction, -10 * direction);
  pros::delay(50);
  // Set drive to zero
  setDrivePower(0, 0);
}

void Drivebase::autoRotate(int targetDegrees, int voltage)
{
  // Rotate function from 4411S's PROS tutorials

  // Direction is either 1 or -1, based on unit circle (CW is positive, CCW is negative)
  direction = abs(targetDegrees) / targetDegrees;
  // Reset gyro
  resetDriveSensors(true);

  // Turn until (degrees - 5) degrees are reached
  setDrivePower(-voltage * direction, voltage * direction);
  while(fabs(gyro.get_value()) < (abs(targetDegrees * 10) - 50)){
    pros::delay(10);
  }
  pros::delay(100);

  // Correcting any overshoot
  if(fabs(gyro.get_value()) > abs(targetDegrees * 10)){
    setDrivePower(0.5 * voltage * direction, 0.5 * -voltage * direction);
    while(fabs(gyro.get_value()) > abs(targetDegrees * 10)){
      pros::delay(10);
    }
  }
  // Correcting any undershoot
  else if(fabs(gyro.get_value()) < abs(targetDegrees * 10)){
    setDrivePower(0.5 * -voltage * direction, 0.5 * voltage * direction);
    while(fabs(gyro.get_value()) < abs(targetDegrees * 10)){
      pros::delay(10);
    }
  }
  // Set drive to zero
  setDrivePower(0, 0);
}

void Drivebase::autoMovePD(int targetValue, int timeout)
{
  // Proportional-Derivative drive function for auton

  // Direction is either 1 or -1, based on target value
  direction = abs(targetValue) / targetValue;

  // Reset timer and motor encoders
  startTime = pros::millis();
  resetDriveSensors(false);

  while((pros::millis() - startTime) < timeout){
    currentValue = getAveDriveEncoderValue();

    // PROPORTIONAL
    error = targetValue - currentValue;
    // DERIVATIVE
    errorDiff = error - errorPrevious; // Difference between current error and previous error
    errorPrevious = error; // Save current error for next cycle
    // Power = P + D
    power = (error * kP) + (errorDiff * kD);

    // Cap power if it's too large or small
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

void Drivebase::autoRotatePD(int targetDegrees, int timeout)
{
  // Proportional-Derivative turn function for auton

  // Direction is either 1 or -1, based on target value
  direction = abs(targetDegrees) / targetDegrees;

  // Reset timer and gyro
  startTime = pros::millis();
  resetDriveSensors(false);

  while((pros::millis() - startTime) < timeout){
    currentDegrees = fabs(gyro.get_value());

    // PROPORTIONAL
    error = targetDegrees - currentDegrees;
    // DERIVATIVE
    errorDiff = error - errorPrevious; // Difference between current error and previous error
    errorPrevious = error; // Save current error for next cycle
    // Power = P + D
    power = (error * kP) + (errorDiff * kD);

    // Cap power if it's too large or small
    if(power > MAX_VOLTAGE){
      power = MAX_VOLTAGE;
    }
    if(power < MIN_VOLTAGE){
      power = MIN_VOLTAGE;
    }
    setDrivePower(-power * direction, power * direction);
    pros::delay(20);
  }
}
