// Задача 15 (5 баллов)
// «Приближенное решение метрической неориентированной задачи коммивояжера». Найдите приближенное решение метрической
// неориентированной задачи коммивояжера в полном графе (на плоскости) с помощью минимального остовного дерева.
// Оцените качество приближения на случайном наборе точек, нормально распределенном на плоскости с дисперсией
// 1. Нормально распределенный набор точек получайте с помощью преобразования Бокса-Мюллера.
// При фиксированном N, количестве вершин графа, несколько раз запустите оценку качества приближения.
// Вычислите среднее значение и среднеквадратичное отклонение качества приближения для данного N.
// Запустите данный эксперимент для всех N в некотором диапазоне, например, [2, 10].
// Автоматизируйте запуск экспериментов.
// В решении требуется разумно разделить код на файлы. Каждому классу - свой заголовочный файл и файл с реализацией.

//
// Created by Петр Полежаев ( polezhaev.ds@gmail.com ) on 19.12.2019.
//


#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "argparse.h"
#include "algorithms.h"
#include "MetricGraph.h"
#include "experiment.h"

const std::size_t DefaultMinVerticesCount = 2;
const std::size_t DefaultMaxVerticesCount = 10;
const std::size_t DefaultRepetitionsCount = 20;


void PrintUsageExample(char* const programName, ArgumentParser& parser) {
    std::cout << "Usage example:" << std::endl;
    std::cout << "    " << programName
              << " -m " << DefaultMinVerticesCount
              << " -M " << DefaultMaxVerticesCount
              << " -r " << DefaultRepetitionsCount
              << std::endl;
}

void PrintLine() {
    std::cout << "---------------------------------------------------------------------------------" << std::endl;
}

template <class T1, class T2, class T3, class T4>
void PrintRow(const T1& firstValue, const T2& secondValue, const T3& thirdValue, const T4& fourthValue) {
    std::cout << "|" << std::setw(10) << firstValue << " |" << std::setw(13) << secondValue << " |"
              << std::setw(27) << thirdValue << " |" << std::setw(22) << fourthValue << " |" << std::endl;
}

std::size_t ParseSizeT(const std::string& str) {
    if (str[0] == '-')
        throw std::out_of_range("Argument is out of range!");
    return std::stoull(str);
}

int main(int argc, char* argv[]) {
    //Parameters of experiment
    std::size_t minVerticesCount = DefaultMinVerticesCount;
    std::size_t maxVerticesCount = DefaultMaxVerticesCount;
    std::size_t repetitionsCount = DefaultRepetitionsCount;
    //Parameters of visualization
    unsigned int numberOfDecimalDigits = 4;

    ArgumentParser parser("Program to compare approximate MST-based and exact solutions for Travelling Salesman Problem");
    parser.add_argument("-m", "--min_size", "minimum number of vertices (default " +
                                            std::to_string(DefaultMinVerticesCount) +  ")", false);
    parser.add_argument("-M", "--max_size", "maximum number of vertices (default " +
                                            std::to_string(DefaultMaxVerticesCount) +  ")", false);
    parser.add_argument("-r", "--repetitions", "number of test repetitions (default " +
                                            std::to_string(DefaultRepetitionsCount) +  ")", false);
    try {
        parser.parse(argc, argv);
    } catch (const ArgumentParser::ArgumentNotFound& ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    if (parser.is_help()) {
        PrintUsageExample(argv[0], parser);
        return 0;
    }

    try {
        if (parser.exists("m"))
            minVerticesCount = ParseSizeT(parser.get<std::string>("m"));
        if (parser.exists("M"))
            maxVerticesCount = ParseSizeT(parser.get<std::string>("M"));
        if (parser.exists("r"))
            repetitionsCount = ParseSizeT(parser.get<std::string>("r"));

        if (minVerticesCount <= 1)
            throw std::invalid_argument("Minimum number of vertices should be at least 2!");
        if (minVerticesCount > maxVerticesCount)
            throw std::invalid_argument("Minimum number cannot exceed maximum number of vertices!");
        if (repetitionsCount == 0)
            throw std::invalid_argument("Repetitions count should be at least 1!");

    } catch (const std::invalid_argument& ex) {
        std::cout << ex.what() << std::endl;
        parser.print_help();
        PrintUsageExample(argv[0], parser);
        return 2;

    } catch (const std::out_of_range& ex) {
        std::cout << ex.what() << std::endl;
        return 3;

    }

    std::cout << "Using parameters:" << std::endl;
    std::cout << " - Minimum number of vertices (--min_size or -m): " << minVerticesCount << std::endl;
    std::cout << " - Maximum number of vertices (--max_size or -M): " << maxVerticesCount << std::endl;
    std::cout << " - Number of test repetitions (--requests or -r): " << repetitionsCount << std::endl;
    std::cout << std::endl;

    std::cout.precision(numberOfDecimalDigits);
    std::cout.setf(std::ios::fixed | std::ios::showpoint);
    std::cout << " Experiment for comparison of the approximate MST-based and the exact solutions" << std::endl;
    std::cout << "                          for Travelling Salesman Problem" << std::endl;
    PrintLine();
    PrintRow("#vertices", "#repetitions", "Mean cost of approx./exact", "Std. of approx./exact");
    PrintLine();

    double meanCostRatio, stdCostRatio;
    std::vector<double> allCostRatios;
    for (std::size_t verticesCount = minVerticesCount; verticesCount <= maxVerticesCount; ++verticesCount) {
        std::vector<double> costRatios = DoExperiment(verticesCount, repetitionsCount, meanCostRatio, stdCostRatio);
        PrintRow(verticesCount, repetitionsCount, meanCostRatio, stdCostRatio);
        allCostRatios.insert(std::end(allCostRatios), std::begin(costRatios), std::end(costRatios));
    }
    PrintLine();
    PrintRow("All cases", "All cases", Mean(allCostRatios), Std(allCostRatios));
    PrintLine();

    return 0;
}
