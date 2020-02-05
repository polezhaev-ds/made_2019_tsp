//
// Created by Петр Полежаев ( polezhaev.ds@gmail.com ) on 19.12.2019.
//

#include <cmath>
#include <random>
#include <cassert>

#include "MetricGraph.h"

std::default_random_engine MetricGraph::generator;
std::uniform_real_distribution<double> MetricGraph::uniform_distribution(-1.0, 1.0 );


void MetricGraph::AddEdge(std::size_t firstVertexId, std::size_t secondVertexId) {
    assert(firstVertexId < vertices.size());
    assert(secondVertexId < vertices.size());

    adjacencyList[firstVertexId].push_back(secondVertexId);
    adjacencyList[secondVertexId].push_back(firstVertexId);
}

void MetricGraph::MakeFullGraph() {
    for (std::size_t i = 0; i < vertices.size() - 1; ++i)
        for (std::size_t j = i + 1; j < vertices.size(); ++j)
            AddEdge(i, j);
}

void MetricGraph::ClearEdges() {
    for (auto& adjList : adjacencyList)
        adjList.clear();
};

const Point2D& MetricGraph::GetPointById(std::size_t vertexId) const {
    assert(vertexId < vertices.size());

    return vertices[vertexId];
}

std::vector<Edge> MetricGraph::GetAllEdges() const {
    std::vector<Edge> result;
    for (std::size_t i = 0; i < vertices.size(); ++i)
        for (auto j : adjacencyList[i])
            if (i <= j)
                result.emplace_back(i, j, vertices[i].DistanceTo(vertices[j]));
    return result;
}

const std::vector<std::size_t>& MetricGraph::GetAdjacentVertexIdsFor(std::size_t vertexId) const {
    assert(vertexId < vertices.size());

    return adjacencyList[vertexId];
}


void MetricGraph::GenerateVertices(std::size_t numberOfVertices) {
    double x, y, s;
    vertices.reserve(numberOfVertices);
    vertices.clear();
    for (std::size_t i = 0; i < numberOfVertices; ++i) {
        //Box-Muller transform https://ru.wikipedia.org/wiki/%D0%9F%D1%80%D0%B5%D0%BE%D0%B1%D1%80%D0%B0%D0%B7%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5_%D0%91%D0%BE%D0%BA%D1%81%D0%B0_%E2%80%94_%D0%9C%D1%8E%D0%BB%D0%BB%D0%B5%D1%80%D0%B0
        do {
            x = MetricGraph::uniform_distribution(MetricGraph::generator);
            y = MetricGraph::uniform_distribution(MetricGraph::generator);
            s = x * x + y * y;
        } while (s > 1 || s == 0);
        x *= std::sqrt(-2 * std::log(s) / s);
        y *= std::sqrt(-2 * std::log(s) / s);
        vertices.emplace_back(x, y);
    }
}