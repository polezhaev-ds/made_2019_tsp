//
// Created by Петр Полежаев ( polezhaev.ds@gmail.com ) on 20.12.2019.
//

#ifndef TASK_15_EXPERIMENT_H
#define TASK_15_EXPERIMENT_H

#include <cctype>
#include <vector>

double Mean(const std::vector<double>& values);

double Std(const std::vector<double>& values);

std::vector<double> DoExperiment(std::size_t verticesCount, std::size_t repetitionsCount, double& meanCostRatio,
        double& stdCostRatio);


#endif //TASK_15_EXPERIMENT_H
