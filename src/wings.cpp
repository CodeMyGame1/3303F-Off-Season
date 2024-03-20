#include "main.h"
#include <vector>

// Wings::Wings(
//     std::uint8_t left_wing_piston_port,
//     std::uint8_t right_wing_piston_port
// ) : left_wing_piston(left_wing_piston_port), right_wing_piston(right_wing_piston_port) {
//     this->close();
// }

Wings::Wings (
    std::vector<std::uint8_t> wing_pistons_ports
) {
    for (std::uint8_t wing_piston_port : wing_pistons_ports) {
        // wing_pistons_ports.push_back();
        pros::ADIDigitalOut temp_piston(wing_piston_port);

        wing_pistons.push_back(temp_piston);
    }
}

// void Wings::update() {
//     left_wing_piston.set_value(wings_enabled);
//     right_wing_piston.set_value(wings_enabled);
// }

void Wings::update() {
    for (pros::ADIDigitalOut wing_piston : wing_pistons) {
        wing_piston.set_value(wings_enabled);
    }
}

void Wings::close() {
    wings_enabled = false;
  
    this->update();
}

void Wings::open() {
    wings_enabled = true;

    this->update();
}

void Wings::toggle() {
    switch (wings_enabled) {
        case true:
            this->close();
            break;

        case false:
            this->open();
            break;
    }
}