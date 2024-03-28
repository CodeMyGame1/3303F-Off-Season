/**
 * TODO: make it so that autons only open ONE WING when opening both would end up hitting the wall! 
 * 
 * do we need to split wing class into having left and right wing open and close?
*/

#pragma once

#include "main.h"

/**
 * Moves FORWARD 10 inches
*/
void auton_test();

/**
 * Moves FORWARD 24 inches
*/
void pid_move_test();

/**
 * Turns RIGHT 90 degrees
*/
void pid_turn_test();

// 6 ball win point?
void far_side_rush();

// some-amount-of-triball win point?
void near_side_rush();