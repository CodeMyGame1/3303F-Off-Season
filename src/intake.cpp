#include "main.h"

/**
 * uses motors:
*/
Intake::Intake(std::int8_t intake_motor_port, pros::motor_brake_mode_e brake_mode) : intake_motor(intake_motor_port) {
    brake_mode = brake_mode;
}

void Intake::intake() {
    intake_motor.move(-127);
}

void Intake::outake() {
    intake_motor.move(127);
}

void Intake::brake() {
    intake_motor.brake();
}