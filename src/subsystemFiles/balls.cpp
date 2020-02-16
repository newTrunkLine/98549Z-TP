#include "main.h"

// =============================================================================
//                              Helper Functions
// =============================================================================

void Balls::setIntakePower(int power)
{
  // Sets the voltage for the intake motor
  intake.move(power);
}

void Balls::setFWPower(int power)
{
  // Sets the voltage for each flywheel motor
  flywheelTop.move(power);
  flywheelBottom.move(power);
}

// =============================================================================
//                          Driver Control Functions
// =============================================================================

void Balls::driverControl()
{
  // Intake Control
  // Top right trigger (R1) intakes and bottom right trigger (R2) outtakes
  m_intakePower = MAX_VOLTAGE * (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)
                            - master.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
  setIntakePower(m_intakePower);

  // Flywheel Control
  // Up button sets flywheel power to maximum voltage
  if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
    setFWPower(MAX_VOLTAGE);
  }
  // Down button sets flywheel to a lower voltage
  else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
    setFWPower(LOW_VOLTAGE);
  }
  else{
    setFWPower(0);
  }
}
