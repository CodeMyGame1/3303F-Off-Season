#pragma once

#include "main.h"

class Wings {
    public:
        std::vector<pros::ADIDigitalOut> wing_pistons;

        bool wings_enabled = false;

        /**
         * initializes the wing subsystems
         * 
         * NOTE that solenoid ports (`pros::ADIDigitalOut` instances) are stored in a
         * VECTOR (`Wings::wing_pistons`)
        */
        Wings(std::vector<std::uint8_t> wing_pistons_ports);

        /**
         * Updates wing state based on `wings_enabled` class variable! 
        */
        void update();

        /**
         * Sets `wings_enabled` to "false"; closes wings
        */
        void close();

        /**
         * Sets `wings_enabled` to "false"; opens wings
        */
        void open();

        /**
         * Toggles wing state (`wings_enabled = !wings_enabled`)
        */
        void toggle();
};