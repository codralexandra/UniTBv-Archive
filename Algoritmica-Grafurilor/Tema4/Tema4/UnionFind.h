#pragma once
#include <vector>
class UnionFind
{
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    UnionFind(int size);

    int Find(int x);

    void Union(int x, int y);
};

