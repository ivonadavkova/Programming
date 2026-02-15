//union find 1971. Find if Path Exists in Graph

#include <vector>
#include <numeric>
using namespace std;

class UnionFind {
public:
    vector<int> parent;
    // Konstruktor: Sekoj jazel e sam svoj roditel
    UnionFind(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    // Naogjanje koren so kompresija na pateka (Path Compression)
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    // Spojuvanje na dve grupi (Union)
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) parent[root_i] = root_j;
    }
};

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        // 1. Ako startot i celta se isti, patekata sekako postoi
        if (source == destination) return true;
        // 2. Kreirame UnionFind struktura za n jazli
        UnionFind uf(n);
        // 3. Gi minuvame site vrski (edges) i gi spojuvame jazlite vo grupi
        for (auto& edge : edges) {
            uf.unite(edge[0], edge[1]);
        }
        // 4. Proveruvame dali source i destination imaat ist koren (ist gazda)
        return uf.find(source) == uf.find(destination);
    }
};
