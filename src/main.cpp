/**
 * IT'S IMPORTANT TO NOTE THAT THE AUTON CODE TREATS THE INTAKE AS THE FRONT,
 * WHILE WHEN ACTUALLY DRIVING, THE NON-INTAKE SIDE OF THE ROBOT IS THE FRONT
*/

#include "main.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"

// maximum drive speed for drivetrain
const int DRIVE_SPEED = 127;
// amount of time, in milliseconds, to delay between each pros `opcontrol()` loop
const int DELAY_TIME = 20;

// left horiz A
// right horiz B
// vert wing C
// hang ratchet D

// -1 3

// seeems to be correcttt
// 1 -3

// one side go faster
// 1 3
// -1 -3

pros::Controller controller(pros::E_CONTROLLER_MASTER);

// left motor definitions -- all reversed, EXCEPT for middle (normal!)
pros::Motor left_back_motor(20);
pros::Motor left_front_middle_motor(-18);
pros::Motor left_back_middle_motor(19);
// pros::Motor left_front_motor(1);
pros::Motor left_front_motor(1);

// right motor definitions -- all normal, EXCEPT for middle (reversed!)
pros::Motor right_back_motor(13); // ACTUAL BACK
pros::Motor right_back_middle_motor(-12);
pros::Motor right_front_middle_motor(11);
// pros::Motor right_front_motor(-3);
pros::Motor right_front_motor(3);

// auton left 1

// motors reversed
pros::Motor_Group left_motors({
	left_back_motor
	, left_back_middle_motor
	, left_front_middle_motor
	, left_front_motor
});
pros::Motor_Group right_motors({
	right_back_motor
	, right_back_middle_motor
	, right_front_middle_motor
	, right_front_motor
});

pros::Imu inertial_sensor(2); 

// lemlib

lemlib::OdomSensors sensors {
    nullptr 			// vertical tracking wheel 1
    , nullptr 			// vertical tracking wheel 2
    , nullptr 			// horizontal tracking wheel 1
    , nullptr 			// we don't have a second tracking wheel, so we set it to nullptr
    , &inertial_sensor 	// inertial sensor
};

lemlib::Drivetrain drivetrain(
	&left_motors, 
	&right_motors, 
	17, 
	2.75, 
	600, 
	lemlib::Omniwheel::NEW_275
);

// kP 6 -> starts overshooting w/o oscillation
// kP 10 -> overshot more, SLIGHT oscillation!
// kD 6 -> why is it still oscillating?!?!?!
lemlib::ControllerSettings linearController( // amon gus
	10 		// kP (proportional constant for PID)
	, 0 	// kI (integral constant for PID)
	, 12 	// kD (derivative constant for PID)
	, 0 	// anti-windup term (prevents large overshoots/oscillations)
	, 1		// small error (the error at which the PID will switch to a slower control loop)
	, 100	// small error timeout (how long the PID will wait before switching to a slower control loop)
	, 3		// large error (the error at which the PID) will switch to a faster control loop
	, 500	// large error timeout (how long the PID will wait before switching to a faster control loop)
	, 0		// slew rate (the maximum acceleration of the PID)
);

lemlib::ControllerSettings angularController(
	3 	// kP (proportional constant for PID)
	, 0 	// kI (integral constant for PID)
	, 16 	// kD (derivative constant for PID)
	, 0 	// anti-windup term (prevents large overshoots/oscillations)
	, 1		// small error (the error at which the PID will switch to a slower control loop)
	, 100	// small error timeout (how long the PID will wait before switching to a slower control loop)
	, 3		// large error (the error at which the PID)// slew rate (the maximum acceleration of the PID) will switch to a faster control loop)
	, 500	// large error timeout (how long the PID will wait before switching to a faster control loop)
	, 0		// slew rate (the maximum acceleration of the PID)
);

lemlib::Chassis chassis(
	drivetrain
	, linearController
	, angularController
	, sensors
);

/**
 * TODO: set vertical wing & horizontal wing ports & hang ratchet ports
*/
Wings left_vert_wing = Wings('A');

Wings horiz_wings = Wings('A', 'A');

Hang hang = Hang({
	10
	, 'A' 
});

Intake intake = Intake(
	-17,
	pros::E_MOTOR_BRAKE_HOLD
);

void screenTaskFunc(void* chassis) {
	// we need to pass in chassis as a void* type, and then
	// cast void* to lemlib::Chassis* within the function because 
	// pros is kinda dumb ngl
	lemlib::Chassis *myChassis = (lemlib::Chassis *)chassis;

	while (true) {
		// print robot location & heading to the brain screen
		pros::lcd::print(4, "X: %f", myChassis->getPose().x); // x
		pros::lcd::print(5, "Y: %f", myChassis->getPose().y); // y
		pros::lcd::print(6, "Heading: %f", myChassis->getPose().theta); // heading
		pros::lcd::print(7, "IMU Heading: %f", inertial_sensor.get_heading()); // IMU heading
		
		// log position telemetry
		lemlib::telemetrySink()->info(
			"Chassis pose: {}"
			, myChassis->getPose()
		);
		
		// delay to save resources
		pros::delay(DELAY_TIME);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();

	chassis.calibrate();

	inertial_sensor.reset();

	pros::Task screenTask(screenTaskFunc, &chassis);

	//Aarav farted all over the robot
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	printf("and may god save our souls");

	// pid_turn_test();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	left_motors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
	right_motors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);

	while (true) {
		/**
		 * MOVEMENT
		*/

		chassis.arcade(controller.get_analog(ANALOG_RIGHT_X), -controller.get_analog(ANALOG_LEFT_Y));

		/**
		 * END MOVEMENT
		*/


		/**
		 * FETCHING CONTROLS
		*/

		// TOGGLE CONTROLS

		// horizontal wings
		bool L1_new_press = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1);
		// left vertical wing
		bool DOWN_new_press = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN);
		// hang ratchet
		bool UP_new_press = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP);


		// HOLD CONTROLS

		// hang - up
		bool B_pressed = controller.get_digital(pros::E_CONTROLLER_DIGITAL_B);
		// hang - down
		bool X_pressed = controller.get_digital(pros::E_CONTROLLER_DIGITAL_X);

		bool R1_pressed = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
		bool R2_pressed = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
		
		/**
		 * END FETCHING CONTROLS
		*/

		
		/**
		 * HANDLING CONTROLS
		*/

		if (R1_pressed == R2_pressed) {
			intake.brake();
		} else if (R1_pressed) {
			intake.intake();
		} else if (R2_pressed) {
			intake.outake();
		}

		if (L1_new_press) {
			horiz_wings.toggle();
		}

		if (DOWN_new_press) {
			left_vert_wing.toggle();
		}

		if (UP_new_press) {
			hang.ratchet();
		}

		// if hang wants to be both opened and closed, or buttons aren't being pressed, brake the hang
		if (B_pressed == X_pressed) {
			hang.stop_hang();
		// open hang (hold)
		} else if (B_pressed) {
			hang.open_hang();
		// close hang (hold)
		} else if (X_pressed) {
			hang.close_hang();
		}

		/**
		 * END HANDLING CONTROLS
		*/


		/**
		 * REQUIRED DELAY
		*/
		pros::delay(DELAY_TIME);
	}
}
