#include "UnionFind.h"

UnionFind::UnionFind(int size)
{
    parent.resize(size);
    rank.resize(size, 0);

    for (int i = 0; i < size; i++)
    {
        parent[i] = i;
    }
}

int UnionFind::Find(int x)
{
    if (parent[x] != x)
    {
        parent[x] = Find(parent[x]);
    }
    return parent[x];
}

void UnionFind::Union(int x, int y)
{
    int rootX = Find(x);
    int rootY = Find(y);

    if (rootX != rootY)
    {
        if (rank[rootX] < rank[rootY])
        {
            parent[rootX] = rootY;
        }
        else if (rank[rootX] > rank[rootY])
        {
            parent[rootY] = rootX;
        }
        else
        {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}


