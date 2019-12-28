#include "main.h"

// Helper Functions
void Caps::setDescorerPower(int power)
{
  descorer = power;
}

// Driver Control Functions
void Caps::driverControl()
{
  // Descorer Control
  // Top left trigger (L1) raises descorer and bottom left trigger (L2) lowers descorer
  int descorerPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2));
}
