#include "main.h"

// Constants
const int MAX_VOLTAGE = 127;
const int LOW_VOLTAGE = 85;

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
  int intakePower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
  setIntakePower(intakePower);

  // Flywheel Control
  // Up button sets flywheel power to maximum voltage
  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
    setFlywheelPower(MAX_VOLTAGE);
  }
  // Down button sets flywheel to a lower voltage
  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
    setFlywheelPower(LOW_VOLTAGE);
  }
  else{
    setFlywheelPower(0);
  }
}
