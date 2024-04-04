#pragma once

#include "main.h"
#include <vector>

class Intake {
    public:
        // pros::Motor intake_motor;

        pros::Motor_Group intake_motors;

        pros::motor_brake_mode_e brake_mode;

        /**
         * initializes the intake subsystem
         * 
         * sets intake motor brake mode to provided `brake_mode`!
        */
        Intake(std::vector<std::int8_t> intake_motor_ports, pros::motor_brake_mode_e brake_mode);

        /**
         * runs the intake motor counterclockwise (AT MAX SPEED, -127), intaking triballs
        */
        void intake();

        /**
         * runs the intake motor clockwise (AT MAX SPEED; 127), outtaking triballs
        */
        void outake();

        /**
         * brakes the intake motor, preventing triballs from falling out or stopping intake/outtake
         * functionality
        */
        void brake();
};