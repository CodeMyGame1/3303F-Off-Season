/**
 * things to keep in mind:
 * - length of bot ("height"): 21 inches (including intake -- 17 inches without)
 * - width of bot: 15.5 inches
 * 
 * previous robot dimensions for autons (before states rebuild):
 * - WIDTH: 14
 * - HEIGHT: 17.5
*/

#pragma once

#include "main.h"

/**
 * Drives directly forward.
 * 
 * Useful for testing LemLib's linear PID controller
*/
void pidLinearTest();

/**
 * Turns 90 degrees right.
 * 
 * Useful for testing LemLib's angular PID controller
*/
void pidAngularTest();

/**
 * Drives straight along the entire length of the central (long) barrier
 * 
 * Useful for making sure that the robot actually works (and is calibrated correctly)
*/
void autonTest();

/**
 * A rush auton developed for the near side
 * 
 * Ideally:
 * - scores alliance triball
 * - gets triball out of matchload zone
 * - touches horizontal elevation bar (with zipties)
 * - pushes 3 triballs (3 * 2 = 6 extra points!) to our own offensive zone
*/
void near_side_rush();

/**
 * A rush auton developed for the far side
*/
void far_side_rush();

// /**
//  * GOAL: RAHHH. AS MANY TRIBALLS AS POSSIBLE. SCORE!!!
//  * 
//  * REFERENCE: https://www.youtube.com/watch?v=c86VTALprxo
// */
// void prog_skills_max();