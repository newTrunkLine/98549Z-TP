#ifndef CLASSES_HPP
#define CLASSES_HPP

class Drivebase
{
public:
  // Initialize Variables
  Drivebase();

  // Helper Functions
  void setDrivePower(int left, int right);
  void resetDriveSensors(bool resetGyro);
  double getAveDriveEncoderValue();
  int getExpoValue(int joystickValue);

  // Driver Control Functions
  void driverControlTank();
  void driverControlArcade();

  // Autonomous Functions
  void autoMove(int targetValue, int voltage);
  void autoRotate(int targetDegrees, int voltage);

private:
  int m_output;
  int m_driveExponent;
  int m_leftPower;
  int m_rightPower;
  int m_arcadeY;
  int m_arcadeX;
  int m_direction;
};

class Balls
{
public:
  // Helper Functions
  void setIntakePower(int power);
  void setFWPower(int power);

  // Driver Control Functions
  void driverControl();

private:
  int m_intakePower;
};

class Caps
{
public:
  // Helper Functions
  void setDescorerPower(int power);

  // Driver Control Functions
  void driverControl();

private:
  int m_descorerPower;
};

#endif
