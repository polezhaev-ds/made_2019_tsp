//
// Created by Петр Полежаев ( polezhaev.ds@gmail.com ) on 19.12.2019.
//

#include <cassert>
#include "DisjointSetUnion.h"


void DisjointSetUnion::MakeSet(std::size_t item) {
    assert(item < nodes.size());

    nodes[item] = SetNode(item);
}

std::size_t DisjointSetUnion::FindSet(std::size_t item) {
    assert(item < nodes.size());

    std::size_t root = item;
    while (nodes[root].ParentIndex != root) {
        root = nodes[root].ParentIndex;
    }
    std::size_t parent;
    while (item != root) {
        parent = nodes[item].ParentIndex;
        nodes[item].ParentIndex = root;
        item = parent;
    }
    return root;
}

void DisjointSetUnion::Union(std::size_t x, std::size_t y) {
    assert(x < nodes.size());
    assert(y < nodes.size());

    x = FindSet(x);
    y = FindSet(y);
    if (x != y) {
        if (nodes[x].Rank < nodes[y].Rank)
            std::swap(x, y);
        nodes[y].ParentIndex = x;
        nodes[x].Rank += nodes[y].Rank;
    }
}