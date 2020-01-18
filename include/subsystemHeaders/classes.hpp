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
  void autoMovePD(int targetValue, int timeout);
  void autoRotatePD(int targetDegrees, int timeout);

private:
  int output;
  int leftPower;
  int rightPower;
  int arcadeY;
  int arcadeX;
  int direction;
  float kP;
  float kD;
  int currentValue;
  int currentDegrees;
  int error;
  int errorDiff;
  int errorPrevious;
  int power;
  int startTime;
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
  int intakePower;
};

class Caps
{
public:
  // Helper Functions
  void setDescorerPower(int power);

  // Driver Control Functions
  void driverControl();

private:
  int descorerPower;
};

#endif
