//
// Created by Петр Полежаев ( polezhaev.ds@gmail.com ) on 19.12.2019.
//

#ifndef TASK_15_EDGE_H
#define TASK_15_EDGE_H

#include <cctype>
#include <limits>

class Edge {
public:
    explicit Edge(std::size_t firstVertexId=std::numeric_limits<std::size_t>::max(),
                  std::size_t secondVertexId = std::numeric_limits<std::size_t>::max(), std::size_t weight = 0ull):
            firstVertexId(firstVertexId),
            secondVertexId(secondVertexId),
            weight(weight)
    {
    }

    [[nodiscard]] std::size_t GetFirstVertexId() const {
        return firstVertexId;
    }

    [[nodiscard]] std::size_t GetSecondVertexId() const {
        return secondVertexId;
    }

    [[nodiscard]] double GetWeight() const {
        return weight;
    }

private:
    std::size_t firstVertexId;
    std::size_t secondVertexId;
    double weight;

};


#endif //TASK_15_EDGE_H
