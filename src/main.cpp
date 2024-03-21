#include "main.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"

// maximum drive speed for drivetrain
const int DRIVE_SPEED = 127;
// amount of time, in milliseconds, to delay between each pros `opcontrol()` loop
const int DELAY_TIME = 20;

pros::Controller controller(pros::E_CONTROLLER_MASTER);

/**
 * TODO: set ports
*/
// left motor definitions -- all reversed!
pros::Motor left_back_motor(-0);
pros::Motor left_middle_motor(-0);
pros::Motor left_front_motor(-0);

// right motor definitions -- all normal!
pros::Motor right_back_motor(0);
pros::Motor right_middle_motor(0);
pros::Motor right_front_motor(0);

// motors reversed
pros::Motor_Group left_motors({
	left_back_motor
	, left_middle_motor
	, left_front_motor
});
pros::Motor_Group right_motors({
	right_back_motor
	, right_middle_motor
	, right_front_motor
});

pros::IMU inertial_sensor(0); 

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

lemlib::ControllerSettings linearController(
	9 		// kP (proportional constant for PID)
	, 0 	// kI (integral constant for PID)
	, 7 	// kD (derivative constant for PID)
	, 0 	// anti-windup term (prevents large overshoots/oscillations)
	, 1		// small error (the error at which the PID will switch to a slower control loop)
	, 100	// small error timeout (how long the PID will wait before switching to a slower control loop)
	, 3		// large error (the error at which the PID) will switch to a faster control loop
	, 500	// large error timeout (how long the PID will wait before switching to a faster control loop)
	, 0		// slew rate (the maximum acceleration of the PID)
);

lemlib::ControllerSettings angularController(
	3 		// kP (proportional constant for PID)
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
 * TODO: set vertical wing & horizontal wing ports
*/
Wings left_vert_wing = Wings({
	'A'
});

Wings horiz_wings = Wings({
	'A'
});

/**
 * TODO: set hang ports!
*/
Hang hang = Hang({
	0
	, 'A' 
});


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
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
void autonomous() {}

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

		chassis.arcade(-controller.get_analog(ANALOG_RIGHT_Y), controller.get_analog(ANALOG_LEFT_X));

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
		
		/**
		 * END FETCHING CONTROLS
		*/

		
		/**
		 * HANDLING CONTROLS
		*/

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
		if (!(B_pressed and X_pressed)) {
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
