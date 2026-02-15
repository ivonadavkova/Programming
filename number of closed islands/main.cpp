//union find 1254. Number of Closed Islands


#include <vector>
#include <numeric>

using namespace std;

class UnionFind {
public:
    vector<int> parent;
    UnionFind(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0); // Sekoj element e sam svoj roditel na pochetok
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]); // Kompresija na pateka
    }
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) parent[root_i] = root_j; // Gi spojuvame grupite
    }
};

class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int R = grid.size(), C = grid[0].size();
        UnionFind uf(R * C + 1); // +1 za specijalniot "nadvoreshen" jazel
        int dummy = R * C; // Оvoj jazel ja pretstavuva "vodata" ili rabot

        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (grid[i][j] == 0) {
                    int curr = i * C + j;
                    // Ako e na rab, povrzi go so dummy jazelot
                    if (i == 0 || i == R - 1 || j == 0 || j == C - 1) {
                        uf.unite(curr, dummy);
                    }
                    // Proveri sosedi (desno i dolu) i povrzi gi kopnenite delovi
                    if (i + 1 < R && grid[i+1][j] == 0) uf.unite(curr, (i + 1) * C + j);
                    if (j + 1 < C && grid[i][j+1] == 0) uf.unite(curr, i * C + (j + 1));
                }
            }
        }

        int count = 0;
        vector<bool> isRootCounted(R * C + 1, false);
        int dummyRoot = uf.find(dummy);

        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (grid[i][j] == 0) {
                    int root = uf.find(i * C + j);
                    // Ako korenot ne e povrzan so rabot i ne sme go izbrojale vekje
                    if (root != dummyRoot && !isRootCounted[root]) {
                        count++;
                        isRootCounted[root] = true;
                    }
                }
            }
        }
        return count;
    }
};
