/**
 * TODO: switch to lvgl!
*/

// lvgl auton selector todo:

// /**
//  * IN reference auton selector:
//  * todo: implement ability to pass custom autons to function (lines 71 - 75)
//  * todo: set custom theme (lines 81 - 82)
//  * 
//  * EXTRA:
//  * todo: implement ability to dynamically define size of the const char*[] array
//  * todo: implement ability to run "test" autons!
//  * todo: make some members (functions) private, and some public!
// */

#pragma once

#include "main.h"

namespace LLEMUSelector {
    /**
     * initializes the custom-made autonomous selector (that uses the PROS LLEMU)
     * 
     * make sure to pass in all autons as a map with the following format:
     * `std::map<std::string, std::function<void()>>`
     * 
     * `far_side_auton_map` - map of **far** side auton names, and their respective functions
     * `near_side_auton_map` - map of **near** side auton names, and their respective functions
     * `skills_side_auton_map` - map of **skills** auton names, and their respective functions
    */
    void init(
        std::map<std::string, std::function<void()>>& far_side_auton_map
        , std::map<std::string, std::function<void()>>& near_side_auton_map
        , std::map<std::string, std::function<void()>>& skills_auton_map
    );

    /**
     * binds the LLEMU buttons to the auton selector's scrolling / selecting functions
    */
    void rebind();

    /**
     * returns:
     * - `std::map<std::string, std::function<void()>>::iterator`
     *   - represents an iterator pointing to the currently selected auton in the given auton map
    */
    std::map<std::string, std::function<void()>>::iterator fetch_curr_auton();

    /**
     * displays the currently selected "tab" (auton map), and the currently selected auton
     * if in the auton selection state
    */
    void display();

    /**
     * callback function for the left button (btn0) in the PROS LLEMU
     * binded using `pros::lcd::register_btn0_cb()` in `LLEMUSelector::rebind()`
     * 
     * scrolls left between auton "tabs" (`LLEMUSelector::selectingTab` = true)
     * or autons themselves (`LLEMUSelector::selectingTab` = false)
    */
    void left_tab();

    /**
     * callback function for the middle button (btn1) in the PROS LLEMU
     * binded using `pros::lcd::register_btn1_cb()` in `LLEMUSelector::rebind()`
     * 
     * switches from tab selection state to auton selection state (`LLEMUSelector::selectingTab` = true)
     * or calls the currently selected auton (`LLEMUSelector::selectingTab` = false)
    */
    void middle_tab();

    /**
     * callback function for the left button (btn0) in the PROS LLEMU
     * binded using `pros::lcd::register_btn0_cb()` in `LLEMUSelector::rebind()`
     * 
     * scrolls right between auton "tabs" (`LLEMUSelector::selectingTab` = true)
     * or autons themselves (`LLEMUSelector::selectingTab` = false)
    */
    void right_tab();

    /**
     * calls the currently selected auton
    */
    void call();
};