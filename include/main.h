#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "subsystemHeaders/classes.hpp"

// Controller
extern pros::Controller controller;

// Motors
extern pros::Motor driveLeftFront;
extern pros::Motor driveLeftBack;
extern pros::Motor driveRightFront;
extern pros::Motor driveRightBack;
extern pros::Motor flywheelTop;
extern pros::Motor flywheelBottom;
extern pros::Motor intake;
extern pros::Motor descorer;

// Sensors
extern pros::ADIGyro gyro;

// Subsystem Classes
extern Drivebase drivebase;
extern Balls balls;
extern Caps caps;

// Defines
#define JOYSTICK_DEADZONE 8
#define MAX_VOLTAGE 127
#define LOW_VOLTAGE 80
#define MIN_VOLTAGE -127

#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
//#include <iostream>

#endif

#endif  // _PROS_MAIN_H_
