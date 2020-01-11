#include "main.h"

// Initialize Variables
Balls::Balls()
{
  minVoltage = -127;
  maxVoltage = 127;
}

// Helper Functions
void Balls::setIntakePower(int power)
{
  intake = power;
}

void Balls::setFlywheelPower(int power)
{
  flywheelTop = power;
  flywheelBottom = power;
}

// Driver Control Functions
void Balls::driverControl()
{
  // Intake Control
  // Top right trigger (R1) intakes and bottom right trigger (R2) outtakes
  intakePower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
  setIntakePower(intakePower);

  // Flywheel Control
  // Up button sets flywheel power to maximum voltage
  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
    setFlywheelPower(maxVoltage);
  }
  // Down button sets flywheel to a lower voltage
  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
    setFlywheelPower(minVoltage);
  }
  else{
    setFlywheelPower(0);
  }
}
