#pragma once

#include "pros/adi.hpp"
#include "pros/motors.hpp"

class Hang {
    public:
        // a 
        pros::ADIDigitalOut hang_piston;
        bool hang_piston_enabled = false;

        /**
         * initializes hang subsystem
        */
        Hang(std::uint8_t hang_piston_port);

        // updates the pistons 
        void update();

        /**
         * runs the hang motor clockwise (AT MAX SPEED; 127), opens the hang
        */
        void open_hang();

        /**
         * runs the hang motor counterclockwise (AT MAX SPEED; -127), closing the hang
        */
        void close_hang();
};