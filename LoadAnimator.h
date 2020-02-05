//
// Created by Петр Полежаев ( polezhaev.ds@gmail.com ) on 20.12.2019.
//

#ifndef TASK_15_LOADANIMATOR_H
#define TASK_15_LOADANIMATOR_H

#include <string>

class LoadAnimator {
public:
    explicit LoadAnimator():
        stateIndex(-1)
    {
    }

    void Progress();
    void Clear();

private:
    static const unsigned int statesCount = 4;
    static const std::string states[statesCount];
    int stateIndex;
};


#endif //TASK_15_LOADANIMATOR_H
