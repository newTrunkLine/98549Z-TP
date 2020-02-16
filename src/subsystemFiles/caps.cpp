#include "main.h"

// =============================================================================
//                              Helper Functions
// =============================================================================

void Caps::setDescorerPower(int power)
{
  // Sets the voltage for the descorer motor
  descorer.move(power);
}

// =============================================================================
//                          Driver Control Functions
// =============================================================================

void Caps::driverControl()
{
  // Descorer Control
  // Top left trigger (L1) raises descorer and bottom left trigger (L2) lowers descorer
  m_descorerPower = MAX_VOLTAGE * (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)
                              - master.get_digital(pros::E_CONTROLLER_DIGITAL_L2));
  setDescorerPower(m_descorerPower);
}
