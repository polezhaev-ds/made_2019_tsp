//
// Created by Петр Полежаев ( polezhaev.ds@gmail.com ) on 20.12.2019.
//

#include <iostream>
#include "LoadAnimator.h"


void LoadAnimator::Progress() {
    Clear();
    ++stateIndex;
    if (stateIndex == statesCount)
        stateIndex = 0;
    std::cout.flush();
    std::cout << states[stateIndex];
    std::cout.flush();
}

void LoadAnimator::Clear() {
    if (stateIndex != - 1) {
        std::cout.flush();
        std::cout << '\b';
        std::cout.flush();
    }

}

const std::string LoadAnimator::states[statesCount] = {"|", "/", "-", "\\"};