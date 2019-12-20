//
// Created by Петр Полежаев ( polezhaev.ds@gmail.com ) on 19.12.2019.
//

#ifndef TASK_15_METRICGRAPH_H
#define TASK_15_METRICGRAPH_H

#include <vector>
#include <random>
#include "Point2D.h"
#include "Edge.h"

class MetricGraph {
public:
    explicit MetricGraph(std::size_t verticesCount) {
        GenerateVertices(verticesCount);
        adjacencyList.resize(verticesCount);
    }

    [[nodiscard]] std::size_t VerticesCount() const {
        return vertices.size();
    }

    [[nodiscard]] const Point2D& GetPointById(std::size_t vertexId) const;

    void AddEdge(std::size_t firstVertexId, std::size_t secondVertexId);

    void MakeFullGraph();

    void ClearEdges();

    [[nodiscard]] std::vector<Edge> GetAllEdges() const;

    [[nodiscard]]const std::vector<std::size_t>& GetAdjacentVertexIdsFor(std::size_t vertexId) const;

private:
    std::vector<Point2D> vertices;
    std::vector<std::vector<std::size_t>> adjacencyList;

    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> uniform_distribution;

    void GenerateVertices(std::size_t numberOfVertices);
};



#endif //TASK_15_METRICGRAPH_H
