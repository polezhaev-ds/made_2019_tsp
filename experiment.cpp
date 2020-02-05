//
// Created by Петр Полежаев ( polezhaev.ds@gmail.com ) on 20.12.2019.
//

#include "experiment.h"
#include "MetricGraph.h"
#include "algorithms.h"

double Mean(const std::vector<double>& values) {
    double sum = 0.0;
    for (auto value : values)
        sum += value;
    if (values.empty())
        return 0.0;
    return sum / values.size();
}

double Std(const std::vector<double>& values) {
    double mean = Mean(values);
    double variance = 0.0;
    for (auto value : values)
        variance += (value - mean) * (value - mean);
    if (values.size() > 1)
        variance /= static_cast<double>(values.size() - 1);
    return std::sqrt(variance);
}

std::vector<double> DoExperiment(std::size_t verticesCount, std::size_t repetitionsCount, double& meanCostRatio,
        double& stdCostRatio) {
    std::vector<double> costRatios;

    for (std::size_t i = 0; i < repetitionsCount; ++i) {
        MetricGraph graph(verticesCount);
        graph.MakeFullGraph();

        costRatios.push_back(FindApproximateSolutionCostOfTravellingSalesmanProblem(graph) /
                             FindExactSolutionOfTravellingSalesmanProblem(graph));
    }
    meanCostRatio = Mean(costRatios);
    stdCostRatio = Std(costRatios);
    return costRatios;
}