/**************************************************************
                   INITIALIZATION BRANDING

When robot starts up, the Emu Warfare branding is displayed

Created 6/19/23
Last update 6/19/23

****************************************************************/

#include "main.h"

using namespace pros;

void controllerBranding(Controller controller){
    controller.clear();
    controller.set_text(0,0, "*****   *     *   *   * ");
    controller.set_text(1,0, "*****  *  * *  *  *   * ");
    controller.set_text(2,0, "*****  *   *   *  ***** ");
}

void brainBranding() {
    screen::set_pen(COLOR_SEA_GREEN);
    screen::print(TEXT_MEDIUM, 0, "*****   *     *   *   * ");
    screen::print(TEXT_MEDIUM, 1, "*****  *  * *  *  *   * ");
    screen::print(TEXT_MEDIUM, 2, "*****  *   *   *  ***** ");
    screen::scroll(0, 5);
    screen::print(TEXT_MEDIUM, 3, "*    *    *     ***      * * *    ");
    screen::print(TEXT_MEDIUM, 4, " *  * *  *     * * *     * * *    ");
    screen::print(TEXT_MEDIUM, 5, " **     **    *     *    *     *  ") ;
}

void branding() {
    controllerBranding(Controller1);
    controllerBranding(Controller2);
    brainBranding();
}