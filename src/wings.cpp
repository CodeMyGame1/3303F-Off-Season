#include "wings.hpp"
#include <vector>

Wings::Wings (
    std::vector<std::uint8_t> wing_pistons_ports
) {
    // for every piston port, creates an ADIDigitalOut instance, and stores it in a vector of wing pistons
    for (std::uint8_t wing_piston_port : wing_pistons_ports) {
        pros::ADIDigitalOut temp_piston(wing_piston_port);

        wing_pistons.push_back(temp_piston);
    }
}

void Wings::update() {
    // for every wing in the wing piston vector, sets its value to the current wing state
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
        // if wings are currently open, closes them!
        case true:
            this->close();
            break;

        // if wings are currently closed, opens them!
        case false:
            this->open();
            break;
    }
}