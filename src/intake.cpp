#include "main.h"

// Wings::Wings (
//     std::vector<std::uint8_t> wing_pistons_ports
// ) {
//     // for every piston port, creates an ADIDigitalOut instance, and stores it in a vector of wing pistons
//     for (std::uint8_t wing_piston_port : wing_pistons_ports) {
//         pros::ADIDigitalOut temp_piston(wing_piston_port);

//         wing_pistons.push_back(temp_piston);
//     }
// }

Intake::Intake(
    std::vector<std::int8_t> intake_motor_ports
    , pros::motor_brake_mode_e brake_mode
) : intake_motors(intake_motor_ports) {
    brake_mode = brake_mode;

    intake_motors.set_brake_modes(brake_mode);
}

void Intake::intake() {
    intake_motors.move(-127);
}

void Intake::outake() {
    intake_motors.move(127);
}

void Intake::brake() {
    intake_motors.brake();
}
