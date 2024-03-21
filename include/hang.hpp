#pragma once

#include "pros/adi.hpp"
#include "pros/motors.hpp"

class Hang {
    public:
        pros::Motor hang_motor;
        pros::ADIDigitalOut ratchetPiston;

        /**
         * initializes hang subsystem
         * 
         * INITIALLY RETRACTS RATCHET!
         * 
         * note: encoder units of `Hang::hang_motor` is set to degrees!
        */
        Hang(std::int8_t hang_motor_port, std::uint8_t ratchet_piston_port);

        /**
         * opens and closes the hang, releasing the intake during the start of the autonomous period
        */
        void release_intake();

        /**
         * runs the hang motor clockwise (AT MAX SPEED; 127), opens the hang
        */
        void open_hang();

        /**
         * runs the hang motor counterclockwise (AT MAX SPEED; -127), closing the hang
        */
        void close_hang();

        /**
         * brakes (stops) the hang motor
        */
        void stop_hang();

        /**
         * enables the ratchet piston (ONLY ONE WAY), locking the hang in place
        */
        void ratchet();
};