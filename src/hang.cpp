#include "hang.hpp"

Hang::Hang(
    std::int8_t hang_motor_port
    , std::uint8_t ratchet_piston_port
) : hang_motor(hang_motor_port), ratchetPiston(ratchet_piston_port) {
    hang_motor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    
    ratchetPiston.set_value(0);
};

void Hang::release_intake() {
    /**
     * TODO: need to wait before calling second function?
     * TODO: verify that degree target is correct
    */
    hang_motor.move_relative(-15, 127);
    hang_motor.move_relative(30, 127);
};

void Hang::open_hang() {
    hang_motor.move(127);
};

void Hang::close_hang() {
    hang_motor.move(-127);
}

void Hang::stop_hang() {
    hang_motor.brake();
};

void Hang::ratchet() {
    ratchetPiston.set_value(1);
};