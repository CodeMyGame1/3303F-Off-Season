#include "main.h"

namespace LLEMUSelector {
    std::map<std::string, std::function<void()>> far_side_autons;
    std::map<std::string, std::function<void()>> near_side_autons;
    std::map<std::string, std::function<void()>> skills_autons;

    int currTab;
    int currAuton;

    // if true, will show tabs
    // if false, will show autons FOR current tab
    bool selectingTab = true;

    void init(
        std::map<std::string, std::function<void()>>& far_side_auton_map
        , std::map<std::string, std::function<void()>>& near_side_auton_map
        , std::map<std::string, std::function<void()>>& skills_auton_map
    ) {
        far_side_autons = far_side_auton_map;
        near_side_autons = near_side_auton_map;
        skills_autons = skills_auton_map;

        currTab = 0;
        currAuton = 0;

        // rebind();
    };

    void rebind() {
        pros::lcd::register_btn0_cb(left_tab);
        pros::lcd::register_btn1_cb(middle_tab);
        pros::lcd::register_btn2_cb(right_tab);
    }

    std::map<std::string, std::function<void()>>::iterator fetch_curr_auton() {
        std::map<std::string, std::function<void()>>::iterator it;

        switch (currTab) {
            // far side
            case 0:
                it = far_side_autons.begin();

                break;
            // near side
            case 1:
                it = near_side_autons.begin();

                break;
            // skills
            case 2:
                it = skills_autons.begin();

                break;
        };

        std::advance(it, currAuton);

        return it;
    };

    void display() {
        std::string tabName = "";

        switch (currTab) {
            case 0:
                tabName = "Far Side Autons";

                break;
            case 1:
                tabName = "Near Side Autons";

                break;
            case 2:
                tabName = "Skills Autons";

                break;
        };

        pros::lcd::set_text(0, tabName);

        // additional logic if also selecting auton
        if (selectingTab == false) {
            printf("running this goofy...");

            std::string currAutonText;
            std::map<std::string, std::function<void()>>::iterator curr_auton = fetch_curr_auton();
            currAutonText = curr_auton->first;

            pros::lcd::set_text(1, "-----------------");

            

            pros::lcd::set_text(3, currAutonText);
        };
    };

    void left_tab() {
        switch (selectingTab) {
            case true:
                if (currTab > 0) {
                    currTab -= 1;
                };

                break;
            
            case false:
                if (currAuton > 0) {
                    currAuton -= 1;
                }
                
                break;
        }

        display();
    };

    // toggles selectingTab!
    void middle_tab() {
        // first -> selects tab
        // THEN -> selects auton!

        if (selectingTab == true) {
            selectingTab = false;
        } else {
            pros::lcd::print(7, "CALLING SELECTED AUTON...");

            call();
        }

        display();
    }

    void right_tab() {
        switch (selectingTab) {
            case true:
                if (currTab < 2) {
                    currTab += 1;
                };

                break;
            
            case false:
                if (currAuton < 2) {
                    currAuton += 1;
                };

                break;
        };

        display();
    };

    void call() {
        std::map<std::string, std::function<void()>>::iterator curr_auton = fetch_curr_auton();

        curr_auton->second();
    };
};