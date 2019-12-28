#ifndef CLASSES_HPP
#define CLASSES_HPP

// Contains all declarations of classes used

class Drivebase
{
public:
  // Helper Functions
  void setDrivePower(int left, int right);

  // Driver Control Functions
  void driverControlTank();
  void driverControlSplitArcade();
  void driverControlExpo();

  // Autonomous Functions
};

class Balls
{
public:
  // Helper Functions
  void setIntakePower(int power);
  void setFlywheelPower(int power);

  // Driver Control Functions
  void driverControl();
};

class Caps
{
public:
  // Helper Functions
  void setDescorerPower(int power);

  // Driver Control Functions
  void driverControl();
};

#endif
