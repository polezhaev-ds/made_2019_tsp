cmake_minimum_required(VERSION 3.15)
project(Task_15)

set(CMAKE_CXX_STANDARD 17)

add_executable(tsp main.cpp MetricGraph.cpp MetricGraph.h algorithms.cpp algorithms.h DisjointSetUnion.cpp
        DisjointSetUnion.h Edge.cpp Edge.h Point2D.cpp Point2D.h experiment.cpp experiment.h
        LoadAnimator.cpp LoadAnimator.h argparse.h)