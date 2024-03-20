/**
 * TODO: add back giant "info" comment (put it in main.h) abt all details for bot (controls, ports, etc!)
 * 
 * TODO: should i be using #pragma once everywhere?
*/
#include "main.h"

/**
 * START CONSTS: (GENERAL)
*/

const int DRIVE_SPEED = 127;

/**
 * END CONSTS: (GENERAL)
*/



/**
 * START CONSTS: (PROS)
*/
pros::Controller controller(pros::E_CONTROLLER_MASTER);


// drivetrain motor definitions
pros::Motor left_front(-19);
pros::Motor left_middle(-18);
pros::Motor left_back(-20);

pros::Motor right_front(11);
pros::Motor right_middle(12);
pros::Motor right_back(13);


// drivetrain left/right motor group definitions
pros::Motor_Group left_drive({
	left_front
	, left_middle
	, left_back
});

pros::Motor_Group right_drive({
	right_front
	, right_middle
	, right_back
});


pros::Imu inertial_sensor(1);

/**
 * END CONSTS: (PROS)
*/



/**
 * START CONSTS: (LEMLIB)
*/

lemlib::Drivetrain drivetrain {
    &left_drive 					// left drivetrain motors

    , &right_drive 					// right drivetrain motors
	
    , 17							// (track) width (of le robor)

    , 3.25							// wheel diameter

    , 450 							// wheel rpm

	, lemlib::Omniwheel::NEW_325_HALF 	// chase power (specific to wheel type).
										// in this case, we are using the NEW (wheels NOT colored green)
										// omniwheels!
};


// helps with odometry
lemlib::OdomSensors sensors {
    nullptr 			// vertical tracking wheel 1
    , nullptr 			// vertical tracking wheel 2
    , nullptr 			// horizontal tracking wheel 1
    , nullptr 			// we don't have a second tracking wheel, so we set it to nullptr
    , &inertial_sensor 	// inertial sensor
};


lemlib::ControllerSettings linearController(
	9 		// kP (proportional constant for PID)

	, 0 	// kI (integral constant for PID)

	, 7 	// kD (derivative constant for PID)

	, 0 	// anti-windup term (prevents large overshoots/oscillations)

	, 1		// small error (the error at which the PID
			// will switch to a slower control loop)

	, 100	// small error timeout (how long the PID will wait before
			// switching to a slower control loop)

	, 3		// large error (the error at which the PID)
			// will switch to a faster control loop

	, 500	// large error timeout (how long the PID will wait before
			// switching to a faster control loop)

	, 0		// slew rate (the maximum acceleration of the PID)
);


lemlib::ControllerSettings angularController(
	3 		// kP (proportional constant for PID)

	, 0 	// kI (integral constant for PID)
	
	, 16 	// kD (derivative constant for PID)
	
	, 0 	// anti-windup term (prevents large overshoots/oscillations)
	
	, 1		// small error (the error at which the PID
			// will switch to a slower control loop)
	
	, 100	// small error timeout (how long the PID will wait before
			// switching to a slower control loop)
	
	, 3		// large error (the error at which the PID)// slew rate (the maximum acceleration of the PID)
			// will switch to a faster control loop

	, 500	// large error timeout (how long the PID will wait before
			// switching to a faster control loop)
	
	, 0		// slew rate (the maximum acceleration of the PID)
);


lemlib::Chassis chassis(
	drivetrain
	, linearController
	, angularController
	, sensors
);

/**
 * END CONSTS: (LEMLIB)
*/



/**
 * START CONSTS: (COMPONENTS)
*/

Hang hang = Hang(
	10 							// port for hang motor
	, 'H' 						// port for hang ratchet piston
);

Intake intake = Intake(
	-17							// port for intake motor

	, pros::E_MOTOR_BRAKE_HOLD	// brake mode for intake motor
);

Wings vert_wings = Wings({
	'B'							// port for vertical wings' pistons
});

Wings horiz_wings = Wings({
	'A'							// port for horizontal wings' pistons
});

/**
 * END CONSTS: (COMPONENTS)
*/

/**
 * TESTING: (1)
*/
void screenTaskFunc(void* chassis) {
	// we need to pass in chassis as a void* type, and then
	// cast void* to lemlib::Chassis* within the function because 
	// pros is kinda dumb ngl
	lemlib::Chassis *myChassis = (lemlib::Chassis *)chassis;

	while (true) {
		// print robot location & heading to the brain screen
		pros::lcd::print(4, "X: %f", myChassis->getPose().x); // x
		pros::lcd::print(5, "Y: %f", myChassis->getPose().y); // y
		pros::lcd::print(6, "Theta: %f", myChassis->getPose().theta); // heading
		
		// log position telemetry
		lemlib::telemetrySink()->info(
			"Chassis pose: {}"
			, myChassis->getPose()
		);
		
		// delay to save resources
		pros::delay(50);
	}
}

pros::Task screenTask(screenTaskFunc, &chassis);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	printf("[main.py] initialize(): initializing robot...\n");

	printf("[main.py] initialize(): fetching autons to set for auton selector...\n");
	std::map<std::string, std::function<void()>> far_side_autons;
	std::map<std::string, std::function<void()>> near_side_autons;
	std::map<std::string, std::function<void()>> skills_autons;

	// far_side_autons["far auton 1"] = [&]() { printf("running far auton 1"); };
	// far_side_autons["far auton 2"] = [&]() { printf("running far auton 2"); };
	// far_side_autons["far auton 3"] = [&]() { printf("running far auton 3"); };

	// near_side_autons["near auton 1"] = [&]() { printf("running near auton 1"); };
	// near_side_autons["near auton 2"] = [&]() { printf("running near auton 2"); };
	// near_side_autons["near auton 3"] = [&]() { printf("running near auton 3"); };

	// skills_autons["skills auton 1"] = [&]() { printf("running skills auton 1"); };
	// skills_autons["skills auton 2"] = [&]() { printf("running skills auton 2"); };
	// skills_autons["skills auton 3"] = [&]() { printf("running skills auton 3"); };

	far_side_autons["Far Side Rush"] = far_side_rush;

	near_side_autons["Near Side Rush"] = near_side_rush;

	skills_autons["Push Back"] = [&]() {};

	printf("[main.py] initialize(): initializing pros LCD (LLEMU)...\n");
	pros::lcd::initialize();

	printf("[main.py] initialize(): initializing auton selector...\n");
	// LLEMUSelector::init(
	// 	far_side_autons
	// 	, near_side_autons
	// 	, skills_autons
	// );
	
	// starts screen selecting!
	screenTask.resume();

	printf("[main.py] initialize(): calibrating chassis position...\n");
	
	/**
	 * TODO: sometimes it just flat out doesn't work ;-;
	*/
	chassis.calibrate();

	printf("[main.py] initialize(): finished initializing!\n\n");
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
void competition_initialize() {
	printf("[main.py] competition_initialize(): starting pre-auton initialization...\n");

	printf("[main.py] competition_initialize(): changing drivetrain motors' brake modes...\n");
	left_drive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
	right_drive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);

	printf("[main.py] competition_initialize(): enabling auton selector...\n");
	LLEMUSelector::rebind();

	printf("[main.py] competition_initialize(): finished pre-auton initialization!\n\n");
};

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
	/**
	 * TESTING: (1)
	 * 
	 * NOTE: make sure this doesn't break anything!
	*/

	printf("[main.py] autonomous(): starting autonomous period...\n");

	printf("[main.py] autonomous(): releasing intake...\n");

	hang.release_intake();

	printf("[main.py] autonomous(): calling selected auton!\n");

	// LLEMUSelector::call();

	near_side_rush();

	// far_side_rush();

	printf("[main.py] autonomous(): auton fully finished! (unless auton period ended bfore then ;-;)\n\n");
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
	/**
	 * TESTING: (1)
	 * 
	 * NOTE: make sure this doesn't break anything!
	*/

	printf("[main.py] opcontrol(): starting driver control period...");

	/**
	 * clear auton selector screen displaying stuff
	*/

	// removes artifact text from the auton selector
	pros::lcd::clear();

	printf("[main.py] opcontrol(): disabling auton selector...\n");

	// unbinds all LLEMU buttons
	pros::lcd::register_btn0_cb([]() {});
	pros::lcd::register_btn1_cb([]() {});
	pros::lcd::register_btn2_cb([]() {});

	// sets motor modes to coast for driver control (bc set to 
	// motor brake hold in auton)
	left_drive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
	right_drive.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);

	while (true) {
		// tank drive (scales by max speed DRIVE_SPEED)
		left_drive.move((controller.get_analog(ANALOG_LEFT_Y) / 127.0) * DRIVE_SPEED);
		right_drive.move((controller.get_analog(ANALOG_RIGHT_Y) / 127.0) * DRIVE_SPEED);



		/**
		 * FETCHING CONTROLS:
		*/

		// horizontal wings (toggle)
		bool L1_new_press = controller.get_digital_new_press(DIGITAL_L1);
		// vertical wings (toggle)
		bool LEFT_new_press = controller.get_digital_new_press(DIGITAL_LEFT);
		// ratchet; ONE-WAY toggle (disabled -> enabled)
		bool UP_new_press = controller.get_digital_new_press(DIGITAL_UP);


		// open hang (hold)
		bool L2_pressed = controller.get_digital(DIGITAL_L2);
		// close hang (hold)
		bool B_pressed = controller.get_digital(DIGITAL_B);

		// intake (hold)
		bool R1_pressed = controller.get_digital(DIGITAL_R1);
		// outtake (hold)
		bool R2_pressed = controller.get_digital(DIGITAL_R2);
		
		/**
		 * HANG:
		*/
		if (L2_pressed) {
			// toggles hang (if hang open, it will close. if hang close, it will open)
			hang.open_hang();
		} else if (B_pressed) {
			hang.close_hang();
		} else {
			hang.stop_hang();
		} 

		// ONLY MEANT TO BE USED ONE TIME!!!
		if (UP_new_press) {
			hang.ratchet();
		}

		/**
		 * INTAKE: using motors
		*/
		// if the intake and outtake buttons are either BOTH pressed or BOTH depressed...
		if (R1_pressed == R2_pressed) {
			// don't do anything!
			intake.brake();
		}
		// intake
		else if (R1_pressed) {
			intake.intake();
		}
		// outtake 
		else if (R2_pressed) {
			intake.outake();
		}

		/**
		 * WINGS: VERTICAL
		*/
		// if (L1_pressed) {
		// 	// is it bad to repeatedly .set_value() to 1 with .open() commands like this?
		// 	vert_wings.open();
		// } else {
		// 	vert_wings.close();
		// }
		// if (L2_new_press) {
		// 	vert_wings.toggle();
		// }
		if (LEFT_new_press) {
			vert_wings.toggle();
		}

		/**
		 * WINGS: HORIZONTAL
		*/
		// if (L2_pressed) {
		// 	horiz_wings.open();
		// } else {
		// 	horiz_wings.close();
		// }
		if (L1_new_press) {
			horiz_wings.toggle();
		}

		pros::delay(10);
	}
}