#ifndef CLASSES_HPP
#define CLASSES_HPP

// Contains all declarations of classes used

class Drivebase
{
public:
  // Helper Functions
  void setDrivePower(int left, int right);
  int getExpoValue(int joystickValue);
  void resetDriveSensors();
  double getAveDriveEncoderValue();

  // Driver Control Functions
  void driverControlTank();
  void driverControlStrafe();
  void driverControlArcade();

  // Autonomous Functions
  void autoMove(int targetValue, int voltage);
  void autoRotate(int degrees, int voltage);
  void autoMovePD(int targetValue, int timeout);
  void autoRotatePD(int degrees, int timeout);
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
