//
// Created by Петр Полежаев ( polezhaev.ds@gmail.com ) on 19.12.2019.
//

#ifndef TASK_15_DISJOINTSETUNION_H
#define TASK_15_DISJOINTSETUNION_H

#include <cctype>
#include <vector>
#include <limits>

class DisjointSetUnion {
private:
    class SetNode {
    public:
        std::size_t ParentIndex;
        std::size_t Rank;

        explicit SetNode(std::size_t parentIndex = std::numeric_limits<std::size_t>::max(), std::size_t rank = 1ull):
                ParentIndex(parentIndex),
                Rank(rank)
        {
        }

    };

public:
    explicit DisjointSetUnion(std::size_t size):
            nodes(std::vector<SetNode>(size))
    {
    }


    void MakeSet(std::size_t item);

    std::size_t FindSet(std::size_t item);

    void Union(std::size_t x, std::size_t y);

    [[nodiscard]]std::size_t size() const {
        return nodes.size();
    }

private:
    std::vector<SetNode> nodes;
};


#endif //TASK_15_DISJOINTSETUNION_H
