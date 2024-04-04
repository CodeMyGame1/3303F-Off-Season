#include "wings.hpp"
#include <vector>

/**
 * uses vector (shoves all the ADIDigitalOuts into one vector; indistinguishable)
*/
// Wings::Wings (
//     std::vector<std::uint8_t> wing_pistons_ports
// ) {
//     // for every piston port, creates an ADIDigitalOut instance, and stores it in a vector of wing pistons
//     for (std::uint8_t wing_piston_port : wing_pistons_ports) {
//         pros::ADIDigitalOut temp_piston(wing_piston_port);

//         wing_pistons.push_back(temp_piston);
//     }
// }

// void Wings::update() {
//     // for every wing in the wing piston vector, sets its value to the current wing state
//     for (pros::ADIDigitalOut wing_piston : wing_pistons) {
//         wing_piston.set_value(wings_enabled);
//     }
// }

// void Wings::close() {
//     wings_enabled = false;
  
//     this->update();
// }

// void Wings::open() {
//     wings_enabled = true;

//     this->update();
// }

// void Wings::toggle() {
//     switch (wings_enabled) {
//         // if wings are currently open, closes them!
//         case true:
//             this->close();
//             break;

//         // if wings are currently closed, opens them!
//         case false:
//             this->open();
//             break;
//     }
// }

/**
 * individually stores left and right pistons (if no right piston, as is with the vertical wing, just stores left piston!)
*/
Wings::Wings (
    std::uint8_t left_wing_piston_port
    , std::uint8_t right_wing_piston_port
) {
    // instantiates pros::ADIDigitalOut instances for the left and right wing pistons
    pros::ADIDigitalOut left_wing_piston(left_wing_piston_port);
    pros::ADIDigitalOut right_wing_piston(right_wing_piston_port);

    // adds map entries for the left and right wing pistons
    wing_pistons["left"] = &left_wing_piston;
    wing_pistons["right"] = &right_wing_piston;

    // initializes state of the wing pistons as false
    wing_pistons_enabled["left"] = false;
    wing_pistons_enabled["right"] = false;

    // updates the wing pistons with their state values
    this->update();
}

Wings::Wings (
    std::uint8_t left_wing_piston_port
) {
    // instantiates pros::ADIDigitalOut instances for the left wing piston
    pros::ADIDigitalOut left_wing_piston(left_wing_piston_port);

    // adds a map entry for the left wing piston
    wing_pistons["left"] = &left_wing_piston;

    // initializes the state of the left wing piston as false
    wing_pistons_enabled["left"] = false;

    // updates the left wing piston with its state value
    this->update();
}

void Wings::update(bool updating_left, bool updating_right) {
    // if we have a left wing piston
    if (updating_left && (wing_pistons.find("left") != wing_pistons.end())) {
        wing_pistons["left"]->set_value(wing_pistons_enabled["left"]);
    }

    // if we have a right wing piston
    if (updating_right && (wing_pistons.find("right") != wing_pistons.end())) {
        wing_pistons["right"]->set_value(wing_pistons_enabled["right"]);
    }
}

bool Wings::left_close() {
    if (wing_pistons.find("left") != wing_pistons.end()) {
        wing_pistons_enabled["left"] = false;

        this->update(true, false);

        return true;
    } else {
        return false;
    }
}

bool Wings::right_close() {
    if (wing_pistons.find("right") != wing_pistons.end()) {
        wing_pistons_enabled["right"] = false;

        this->update(false, true);
        
        return true;
    } else {
        return false;
    }
}

bool Wings::left_open() {
    if (wing_pistons.find("left") != wing_pistons.end()) {
        wing_pistons_enabled["left"] = true;

        this->update(true, false);
        
        return true;
    } else {
        return false;
    }
}

bool Wings::right_open() {
    if (wing_pistons.find("right") != wing_pistons.end()) {
        wing_pistons_enabled["right"] = true;

        this->update(false, true);
        
        return true;
    } else {
        return false;
    }
}

void Wings::toggle() {
    wing_pistons_enabled["left"] = !wing_pistons_enabled["left"];
    wing_pistons_enabled["right"] = !wing_pistons_enabled["right"];

    this->update(true, true);
}
