#include "main.h"

/**
 * TODO: should max speed be 127 and min speed by 0? should there be an earlyExitRange?
*/

void auton_test() {
    chassis.moveToPoint(0, 10, 1500, { false, 127, 0, 0 }, false);
};

void pid_move_test() {
    chassis.moveToPoint(0, 24, 5000, { true, 127, 0, 0 }, false);
};

void pid_turn_test() {
    chassis.setPose(0, 0, 0);

    chassis.turnToPoint(0, -30, 5000, { true, 127, 0, 0 }, false);
}

/**
 * reference: https://www.instagram.com/reel/C3guQxvI1Hi (start pos/orientation same as reference!)
 * 
 * each tile is 24"; 2' * 6 tiles = 12' x 12' field dimension!
 * 
 * btw, x is side to side, and y is front and back!
 * 
 * RMBR: FRONT IS THE NON-INTAKE SIDE, SO IF YOU WANT TO USE THE INTAKE, YOU HAVE TO DRIVE IN REVERSE!
 * 
 * TODO: convert to use boomerang PID controller (chassis.moveToPose)!
 * 
 * for all moveToParams and turnToParams:
 * { bool forwards, int maxSpeed, int minSpeed, float earlyExitRange }
*/
void far_side_rush() {
    /**
     * TODO: rewrite autons keeping intake as front!
    */

    // yeet alliance triball
    // horiz_wings.open();
    pros::delay(250);
    // horiz_wings.close();

    // turns to center triball -- FRONT IS THE NON-INTAKE SIDE, SO HAVE TO DRIVE IN REVERSE!
    chassis.turnToPoint(-12, 48, 500, { false, 127, 0, 0 }, false);
    intake.intake();
    // moves to center triball
    /**
     * NOTE: MIGHT BE OVERSHOOTING HERE; adjust distance to account for "height" of bot!
    */ 
    chassis.moveToPoint(-12, 48, 1500, { false, 127, 0, 0 }, false);
    // delay to intake triball
    pros::delay(250);
    // stop intake!
    intake.brake();

    // moves back to start position
    chassis.moveToPoint(0, 0, 1500, { true, 127, 0, 0 }, false);
    // turns toward goal
    chassis.turnToPoint(24, 36, 500, { false, 127, 0, 0 }, false);

    // starts outtaking triball
    intake.outake();
    // waits a bit
    pros::delay(250);
    // finishes outtaking triball!
    intake.brake();

    // turns to elevation bar
    chassis.turnToPoint(-36, 0, 1000, { false, 127, 0, 0 }, false);
    // starts intake
    intake.intake();
    // moves to elevation bar
    /**
     * NOTE: MIGHT BE OVERSHOOTING HERE; adjust distance to account for "height" of bot!
    */
    chassis.moveToPoint(-36, 0, 1000, { false, 127, 0, 0 }, false);
    // waits a bit
    pros::delay(250);
    // stops intake
    intake.brake();

    // moves back with le triball in hand! or intake...?
    chassis.moveToPoint(12, 0, 1000, { true, 127, 0, 0 }, false);

    // turns 45 deg rel to matchload bar
    chassis.turnToPoint(24, 12, 500, { true, 127, 0, 0 }, false);

    // opens the one, lonely vertical wing D:
    // left_vert_wing.open();

    // starts moving (hopefully along matchload bar) and (hopefully) getting the triball out of the matchload bar!
    chassis.moveToPoint(24, 12, 750, { true, 127, 0, 0 }, false);

    // turns toward goal
    chassis.turnToPoint(24, 36, 500, { true, 127, 0, 0 }, true);

    // closes vertical wing (at the same time?)
    // left_vert_wing.close();

    // waits for le turning to turn
    chassis.waitUntilDone();

    // rams into goal! (NOTE: OVERSHOOTS ON PURPOSE SO MAX POWERRRR!!!! TIMEOUT MATTERS HERE!)
    chassis.moveToPoint(24, 48, 1000, { true, 127, 0, 0 }, false);

    // comes back a bit
    chassis.moveToPoint(24, 24, 1000, { false, 127, 0, 0}, false);

    // do a barrel roll
    chassis.turnToPoint(24, 48, 1000, { false, 127, 0, 0}, false);

    // rams into goal (part 2?!?!??!)
    // NOTE: intake SHOULD lift up here, and deposit triball into goal... let's see how that goes!
    // (NOTE: OVERSHOOTS ON PURPOSE SO MAX POWERRRR!!!! TIMEOUT MATTERS HERE!)
    chassis.moveToPoint(24, 48, 1000, { false, 127, 0, 0 }, false);

    // comes back "a bit" (again)
    chassis.moveToPoint(24, 24, 1000, { true, 127, 0, 0 }, false);

    // turns towards that one triball that's like on the side but on the barrier
    chassis.turnToPoint(-36, 36, 500, { false, 127, 0, 0 }, false);

    // starts intake bc why not
    intake.intake();
    // MOVES towards that point?!?!?! that's crazy that you would move where you turn
    chassis.moveToPoint(-36, 36, 1000, { false, 127, 0, 0 }, false);
    // waits for a biiit
    pros::delay(250);
    // stops the intake-?
    intake.brake();

    // turns towards the tile on the right, right in front of the goal
    chassis.turnToPoint(0, 48, 750, { false, 127, 0, 0 }, false);
    // MOVES TOWARDS THAT POINT? THiS IS CRAZY!!!!
    chassis.moveToPoint(0, 48, 1000, { false, 127, 0, 0 }, false);
    // turns towards goal
    chassis.turnToPoint(24, 48, 500, { false, 127, 0, 0 }, false);
    // RAMS INTO GOALL RAHHHHH 
    // (NOTE: OVERSHOOTS ON PURPOSE SO MAX POWERRRR!!!! TIMEOUT MATTERS HERE!)
    chassis.moveToPoint(24, 48, 1000, { false, 127, 0, 0 }, false);

    // move back a "bit"
    chassis.moveToPoint(0, 48, 1000, { true, 127, 0, 0 }, false);
    // turns toward the FINALL TRibALLL
    chassis.turnToPoint(-36, 60, 500, { false, 127, 0, 0 }, false);
    // starts intaking le triball
    intake.intake();
    // moves TOWARDS the final triball!
    chassis.moveToPoint(-36, 60, 1000, { false, 127, 0, 0 }, false);
    // waits a bit
    pros::delay(500);
    // stops intake
    intake.brake();

    // turns towards goal (again...)
    chassis.turnToPoint(24, 60, 750, { false, 127, 0, 0 }, false);
    /**
     * TODO: horizontal wings opening necessary?
    */
    // RAMS into goal!
    chassis.moveToPoint(24, 60, 1500, { false, 127, 0, 0 }, false);
};

/*
 * each tile is 24"; 2' * 6 tiles = 12' x 12' field dimension!
 * 
 * btw, x is side to side, and y is front and back!
 * 
 * RMBR: FRONT IS THE NON-INTAKE SIDE, SO IF YOU WANT TO USE THE INTAKE, YOU HAVE TO DRIVE IN REVERSE!
 * 
 * TODO: convert to use boomerang PID controller (chassis.moveToPose)!
 * 
 * for all moveToParams and turnToParams:
 * { bool forwards, int maxSpeed, int minSpeed, float earlyExitRange }
*/
void near_side_rush() {
    // yeet alliance triball
    // horiz_wings.open();
    pros::delay(250);
    // horiz_wings.close();

    // turn towards center triball
    chassis.turnToPoint(12, 60, 500, { false, 127, 0, 0 }, false);
    // start intake
    intake.intake();
    // move TOWARDS center triball
    chassis.moveToPoint(12, 60, 1000, { false, 127, 0, 0}, false);

    // comes back to initial position
    chassis.moveToPoint(0, 0, 1000, { true, 127, 0, 0 }, false);

    // turns towards elevation bar
    chassis.turnToPoint(36, 0, 750, { false, 127, 0, 0 }, false);

    // outtakes triball
    intake.outake();
    // waits a bit
    pros::delay(250);
    // stops the outtaking
    intake.brake();

    // MOVES towards matchload bar
    chassis.moveToPoint(-12, 0, 1000, { true, 127, 0, 0 }, false);
    // turns 45 deg so robor directed along matchload bar (hopefully)
    chassis.turnToPoint(-24, 12, 500, { true, 127, 0, 0 }, false);

    /**
     * ISSUE: vertical wing on LEFT side of robot, NOT right side... so we'll have to turn robot so intake is facing matchload bar!
    */
};
