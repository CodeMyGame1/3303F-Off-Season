#pragma once

#include "pros/adi.hpp"
// #include <vector>
#include <string>
#include <map>

/**
 * uses vector (shoves all the ADIDigitalOuts into one vector; indistinguishable)
*/
// class Wings {
//     public:
//         std::vector<pros::ADIDigitalOut> wing_pistons;

//         bool wings_enabled = false;

//         /**
//          * initializes the wing subsystems
//          * 
//          * NOTE that solenoid ports (`pros::ADIDigitalOut` instances) are stored in a
//          * VECTOR (`Wings::wing_pistons`)
//         */
//         Wings(std::vector<std::uint8_t> wing_pistons_ports);

//         /**
//          * Updates wing state based on `wings_enabled` class variable! 
//         */
//         void update();

//         /**
//          * Sets `wings_enabled` to "false"; closes wings
//         */
//         void close();

//         /**
//          * Sets `wings_enabled` to "false"; opens wings
//         */
//         void open();

//         /**
//          * Toggles wing state (`wings_enabled = !wings_enabled`)
//         */
//         void toggle();
// };

/**
 * individually stores left and right pistons (if no right piston, as is with the vertical wing, just stores left piston!)
*/
class Wings {
    public:
        std::map<std::string, pros::ADIDigitalOut*> wing_pistons;
        std::map<std::string, bool> wing_pistons_enabled;

        /**
         * general initializer for the wing subsystems
        */
        Wings(std::uint8_t left_wing_piston_port, std::uint8_t right_wing_piston_port);

        /**
         * general initializer for the wing subsystems
         * 
         * (this only allows you to pass in ONE port, as is the case with the vertical wings)
        */
        Wings(std::uint8_t left_wing_piston_port);

        /**
         * Updates wing state based on `wings_enabled` class variable!
         * 
         * `updating_left` and `updating_right` are optional config parameters
         * that determine whether the left/right wing pistons should or should
         * not be updated based on their state values (stored in `wing_pistons_enabled`)
        */
        void update(bool updating_left = true, bool updating_right = true);

        /**
         * Closes the left wing piston
         * 
         * Return `false` if the left wing doesn't exist; else, returns `true`
        */
        bool left_close();

        /**
         * Closes the right wing piston
         * 
         * Return `false` if the right wing doesn't exist; else, returns `true`
        */
        bool right_close();

        /**
         * Opens the left wing piston
         * 
         * Return `false` if the left wing doesn't exist; else, returns `true`
        */
        bool left_open();

        /**
         * Opens the right wing piston
         * 
         * Return `false` if the right wing doesn't exist; else, returns `true`
        */
        bool right_open();

        /**
         * Toggles wing state
        */
        void toggle();
};
