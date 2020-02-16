#include "main.h"

// =============================================================================
//                            Initialize Variables
// =============================================================================

Drivebase::Drivebase()
{
  m_driveExponent = 2;
  m_kP = 0.0;
  m_kD = 0.0;
}

// =============================================================================
//                              Helper Functions
// =============================================================================

void Drivebase::setDrivePower(int left, int right)
{
  // Sets the voltage for each drivebase motor
  driveLeftFront.move(left);
  driveLeftBack.move(left);
  driveRightFront.move(right);
  driveRightBack.move(right);
}

void Drivebase::resetDriveSensors(bool resetGyro)
{
  // Resets the drivebase motor positions to zero
  // If resetGyro is true, the gyro value is also reset to zero
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
  // Return the average position of the drivebase motors
  return (fabs(driveLeftFront.get_position())
        + fabs(driveLeftBack.get_position())
        + fabs(driveRightFront.get_position())
        + fabs(driveRightBack.get_position())) / 4;
}

int Drivebase::getExpoValue(int joystickValue)
{
  // Returns an output value which is less than or equal to the joystick value
  m_output = 0;
  // Output is zero if joystick value is within deadzone
  if(abs(joystickValue) > JOYSTICK_DEADZONE){
    // Direction is the sign of the joystick value (either 1 or -1)
    m_direction = abs(joystickValue) / joystickValue;
    // Joystick value is plugged into the exponential function
    m_output = m_direction * ((pow(abs(joystickValue),m_driveExponent)) / (pow(127,(m_driveExponent - 1))));
  }
  return m_output;
}

// =============================================================================
//                          Driver Control Functions
// =============================================================================

void Drivebase::driverControlTank()
{
  // Basic tank control layout used for debugging
  // Left joystick controls left side of drivebase, right joystick controls right side

  // Get joystick values from controller
  m_leftPower = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  m_rightPower = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  setDrivePower(m_leftPower, m_rightPower);
}

void Drivebase::driverControlArcade()
{
  // Main arcade control used for practice/competiting
  // Left joystick controls the forward/backward motion of the drivebase
  // Right joystick controls drivebase rotation

  // Get joystick values from controller
  m_arcadeY = getExpoValue(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
  m_arcadeX = getExpoValue(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));

  // Combine joystick values before setting drivebase power
  m_leftPower = m_arcadeY + m_arcadeX;
  m_rightPower = m_arcadeY - m_arcadeX;
  setDrivePower(m_leftPower, m_rightPower);
}

// =============================================================================
//                            Autonomous Functions
// =============================================================================

void Drivebase::autoMove(int targetValue, int voltage)
{
  // Drive function from 4411S's PROS tutorials
  // Main drive function used in autonomous to move the drivebase

  // Direction is the sign of the targetValue (either 1 or -1)
  m_direction = abs(targetValue) / targetValue;
  resetDriveSensors(true);

  while(getAveDriveEncoderValue() < abs(targetValue)){
    // Use gyro value to correct deviations
    setDrivePower(voltage * m_direction + gyro.get_value(), voltage * m_direction - gyro.get_value());
    pros::delay(10);
  }
  // Brief break after reaching target
  setDrivePower(-10 * m_direction, -10 * m_direction);
  pros::delay(50);
  // Set drive to zero
  setDrivePower(0, 0);
}

void Drivebase::autoRotate(int targetDegrees, int voltage)
{
  // Rotate function from 4411S's PROS tutorials
  // Main rotate function used in autonomous to rotate the drivebase

  // Direction is the sign of the targetDegrees (either 1 or -1, CW is positive and CCW is negative)
  m_direction = abs(targetDegrees) / targetDegrees;
  resetDriveSensors(true);

  // Turn until (degrees - 5) degrees are reached
  setDrivePower(-voltage * m_direction, voltage * m_direction);
  while(fabs(gyro.get_value()) < (abs(targetDegrees * 10) - 50)){
    pros::delay(10);
  }
  pros::delay(100);

  // Correct any overshoot
  if(fabs(gyro.get_value()) > abs(targetDegrees * 10)){
    setDrivePower(0.5 * voltage * m_direction, 0.5 * -voltage * m_direction);
    while(fabs(gyro.get_value()) > abs(targetDegrees * 10)){
      pros::delay(10);
    }
  }

  // Correct any undershoot
  else if(fabs(gyro.get_value()) < abs(targetDegrees * 10)){
    setDrivePower(0.5 * -voltage * m_direction, 0.5 * voltage * m_direction);
    while(fabs(gyro.get_value()) < abs(targetDegrees * 10)){
      pros::delay(10);
    }
  }
  // Set drive to zero
  setDrivePower(0, 0);
}

void Drivebase::autoMovePD(int targetValue, int timeout)
{
  // Proportional-Derivative drive function used to move drivebase in autonomous

  // Direction is the sign of the targetValue (either 1 or -1)
  m_direction = abs(targetValue) / targetValue;

  // Reset timer and drivebase motor encoders
  m_startTime = pros::millis();
  resetDriveSensors(false);

  while((pros::millis() - m_startTime) < timeout){
    m_currentValue = getAveDriveEncoderValue();

    // PROPORTIONAL
    m_error = targetValue - m_currentValue;
    // DERIVATIVE
    m_errorDiff = m_error - m_errorPrevious; // Difference between current error and previous error
    m_errorPrevious = m_error; // Save current error for next cycle
    // Power = P + D
    m_power = (m_error * m_kP) + (m_errorDiff * m_kD);

    // Cap power if it's too large or small
    if(m_power > MAX_VOLTAGE){
      m_power = MAX_VOLTAGE;
    }
    if(m_power < MIN_VOLTAGE){
      m_power = MIN_VOLTAGE;
    }
    setDrivePower(m_power * m_direction, m_power * m_direction);
    pros::delay(20);
  }
}

void Drivebase::autoRotatePD(int targetDegrees, int timeout)
{
  // Proportional-Derivative turn function for auton

  // Direction is either 1 or -1, based on target value
  m_direction = abs(targetDegrees) / targetDegrees;

  // Reset timer and gyro
  m_startTime = pros::millis();
  resetDriveSensors(true);

  while((pros::millis() - m_startTime) < timeout){
    m_currentDegrees = fabs(gyro.get_value());

    // PROPORTIONAL
    m_error = targetDegrees - m_currentDegrees;
    // DERIVATIVE
    m_errorDiff = m_error - m_errorPrevious; // Difference between current error and previous error
    m_errorPrevious = m_error; // Save current error for next cycle
    // Power = P + D
    m_power = (m_error * m_kP) + (m_errorDiff * m_kD);

    // Cap power if it's too large or small
    if(m_power > MAX_VOLTAGE){
      m_power = MAX_VOLTAGE;
    }
    if(m_power < MIN_VOLTAGE){
      m_power = MIN_VOLTAGE;
    }
    setDrivePower(-m_power * m_direction, m_power * m_direction);
    pros::delay(20);
  }
}
