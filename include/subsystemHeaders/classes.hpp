#ifndef CLASSES_HPP
#define CLASSES_HPP

// Contains all declarations of classes used

class Drivebase
{
public:
  // Initialize Variables
  Drivebase();

  // Helper Functions
  void setDrivePower(int left, int right);
  int getExpoValue(int joystickValue);
  void resetDriveSensors();
  double getAveDriveEncoderValue();

  // Driver Control Functions
  void driverControlTank();
  void driverControlArcade();

  // Autonomous Functions
  void autoMove(int targetValue, int voltage);
  void autoRotate(int degrees, int voltage);
  void autoMovePD(int targetValue, int timeout);
  void autoRotatePD(int degrees, int timeout);

private:
  int joystickDeadzone;
  int minVoltage;
  int maxVoltage;
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
  // Initialize Variables
  Balls();

  // Helper Functions
  void setIntakePower(int power);
  void setFlywheelPower(int power);

  // Driver Control Functions
  void driverControl();

private:
  int minVoltage;
  int maxVoltage;
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
