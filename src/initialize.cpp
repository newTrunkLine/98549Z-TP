#include "main.h"

// Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Motors
pros::Motor driveLeftFront(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftBack(2, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightFront(3, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightBack(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor flywheelTop(5, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor flywheelBottom(6, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intake(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor descorer(8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

// Sensors
pros::ADIGyro gyro('a');

// Subsystem Classes
Drivebase drivebase;
Balls balls;
Caps caps;

void initialize()
{
	pros::lcd::initialize();
	// Set brake type for all motors
	driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	flywheelTop.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	flywheelBottom.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	descorer.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void disabled() {}

void competition_initialize() {}
