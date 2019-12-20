//
// Created by Петр Полежаев ( polezhaev.ds@gmail.com ) on 19.12.2019.
//

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include "DisjointSetUnion.h"
#include "algorithms.h"
#include "MetricGraph.h"
#include "LoadAnimator.h"

static MetricGraph FindMinimumSpanningTreeUsingKruskalAlgorithm(const MetricGraph& graph) {
    auto verticesCount = graph.VerticesCount();
    auto edges = graph.GetAllEdges();

    std::sort(edges.begin(), edges.end(), [](Edge x, Edge y) { return x.GetWeight() < y.GetWeight(); });

    DisjointSetUnion dsu(verticesCount);
    for(size_t i = 0; i < verticesCount; ++i)
        dsu.MakeSet(i);

    MetricGraph minimumSpanningTree = graph;
    minimumSpanningTree.ClearEdges();
    for(const auto& edge : edges) {
        std::size_t firstVertexId = edge.GetFirstVertexId();
        std::size_t secondVertexId = edge.GetSecondVertexId();

        if (dsu.FindSet(firstVertexId) != dsu.FindSet(secondVertexId)) {
            dsu.Union(firstVertexId, secondVertexId);
            minimumSpanningTree.AddEdge(firstVertexId, secondVertexId);
        }
    }

    return minimumSpanningTree;
}

static void CreateTraversalPath(std::size_t currentVertexId, std::size_t prevVertexId,
        const MetricGraph& minimumSpanningTree, std::vector<std::size_t>& traversalPath) {
    traversalPath.push_back(currentVertexId);
    for (auto nextVertexId : minimumSpanningTree.GetAdjacentVertexIdsFor(currentVertexId)) {
        if (nextVertexId != prevVertexId) {
            CreateTraversalPath(nextVertexId, currentVertexId, minimumSpanningTree, traversalPath);
            traversalPath.push_back(currentVertexId);
        }
    }
}

double FindApproximateSolutionCostOfTravellingSalesmanProblem(const MetricGraph& graph) {
    if (graph.VerticesCount() <= 1)
        return 0.0;

    std::size_t emptyVertexId = std::numeric_limits<std::size_t>::max();

    MetricGraph minimumSpanningTree = FindMinimumSpanningTreeUsingKruskalAlgorithm(graph);

    std::vector<std::size_t> traversalPath;
    CreateTraversalPath(0, emptyVertexId, minimumSpanningTree, traversalPath);

    double solutionCost = 0.0;
    std::vector<bool> isVertexProcessed(graph.VerticesCount(), false);
    std::size_t lastNotProcessedVertexId = emptyVertexId;
    for (std::size_t currentVertexId : traversalPath)
        if (!isVertexProcessed[currentVertexId]) {
            isVertexProcessed[currentVertexId] = true;
            if (lastNotProcessedVertexId != emptyVertexId) {
                solutionCost += graph.GetPointById(lastNotProcessedVertexId).DistanceTo(
                        graph.GetPointById(currentVertexId));
            }
            lastNotProcessedVertexId = currentVertexId;
        }
    solutionCost += graph.GetPointById(lastNotProcessedVertexId).DistanceTo(graph.GetPointById(traversalPath[0]));

    return solutionCost;
}


double FindExactSolutionOfTravellingSalesmanProblem(const MetricGraph& graph) {
    std::size_t verticesCount = graph.VerticesCount();

    if (verticesCount <= 1)
        return 0.0;

    LoadAnimator loadAnimator;
    double bestSolutionCost = std::numeric_limits<double>::max();

    std::vector<std::size_t> vertexIdPermutation;
    for (std::size_t i = 0; i < verticesCount; ++i)
        vertexIdPermutation.push_back(i);

    std::size_t i = 1;
    do {
        ++i;
        if (i % 100000 == 0)
            loadAnimator.Progress();

        double currentSolutionCost = 0.0;
        for (std::size_t i = 0; i < verticesCount - 1; ++i)
            currentSolutionCost += graph.GetPointById(vertexIdPermutation[i]).DistanceTo(
                    graph.GetPointById(vertexIdPermutation[i + 1]));
        currentSolutionCost += graph.GetPointById(vertexIdPermutation[vertexIdPermutation.size() - 1]).DistanceTo(
                graph.GetPointById(vertexIdPermutation[0]));

        if (currentSolutionCost < bestSolutionCost)
            bestSolutionCost = currentSolutionCost;

    } while (std::next_permutation(std::begin(vertexIdPermutation), std::end(vertexIdPermutation)));
    loadAnimator.Clear();

    return bestSolutionCost;
}