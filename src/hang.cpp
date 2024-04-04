#include "hang.hpp"

Hang::Hang(
    std::uint8_t hang_piston_port
) : hang_piston(hang_piston_port) {
    // // for every port that codes for a hang piston
    // for (std::uint8_t hang_piston_port : hang_piston_ports) {
    //     // initializes a temporary piston object at that port, setting the piston's state to false
    //     pros::ADIDigitalOut temp_piston(hang_piston_port, hang_pistons_enabled);

    //     // pushes this temporary piston to the vector of hang pistons 
    //     hang_pistons.push_back(temp_piston);
    // };
};

void Hang::update() {
    // for (pros::ADIDigitalOut hang_piston : hang_pistons) {
    //     hang_piston.set_value(hang_pistons_enabled);
    // };

    hang_piston.set_value(hang_piston_enabled);
};

void Hang::open_hang() {
    hang_piston_enabled = true;

    this->update();
};

void Hang::close_hang() {
    hang_piston_enabled = false;

    this->update();
};

/**
 * uses motors:
*/
// Hang::Hang(
//     std::int8_t hang_motor_port
//     , std::uint8_t ratchet_piston_port
// ) : hang_motor(hang_motor_port), ratchetPiston(ratchet_piston_port) {
//     hang_motor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    
//     ratchetPiston.set_value(0);
// };

// void Hang::open_hang() {
//     hang_motor.move(127);
// };

// void Hang::close_hang() {
//     hang_motor.move(-127);
// }

// void Hang::stop_hang() {
//     hang_motor.brake();
// };

// void Hang::ratchet() {
//     ratchetPiston.set_value(1);
// };