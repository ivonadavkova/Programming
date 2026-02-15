#include <vector>
#include <iostream>
#include <string>

using namespace std;

class UnionFind {
private:
    vector<int> parents;
public:
    // Konstruktor: Inicijalizacija na n elementi
    UnionFind(int n) {
        this->parents.resize(n, -1);
    }
    // Obichno naogjanje na koren
    int find(int x) {
        if (this->parents[x] < 0) return x;
        return find(this->parents[x]);
    }
    // Pametno naogjanje so kompresija na patekata
    int smart_find(int x) {
        if (this->parents[x] < 0) return x;
        return this->parents[x] = smart_find(this->parents[x]);
    }
    // Proizvolno obedinuvanje
    void arbitrary_union(int root1, int root2) {
        if (root1 == root2) return;
        this->parents[root1] = root2;
    }
    // Obedinuvanje spored golemina
    void union_by_size(int root1, int root2) {
        if (root1 == root2) return;
        if (this->parents[root1] < this->parents[root2]) {
            this->parents[root1] += this->parents[root2];
            this->parents[root2] = root1;
        } else {
            this->parents[root2] += this->parents[root1];
            this->parents[root1] = root2;
        }
    }
    // Obedinuvanje spored rank (dlabochina)
    void union_by_rank(int root1, int root2) {
        if (root1 == root2) return;
        if (this->parents[root1] < this->parents[root2]) {
            this->parents[root2] = root1;
        } else {
            if (this->parents[root1] == this->parents[root2]) this->parents[root1]--;
            this->parents[root1] = root2;
        }
    }
    // Glavna funkcija za obedinuvanje
    void unite(int x, int y, const string& strategy, const string& findType) {
        int root1, root2;
        if (findType == "simple") {
            root1 = find(x);
            root2 = find(y);
        } else {
            root1 = smart_find(x);
            root2 = smart_find(y);
        }
        if (root1 == root2) return;
        if (strategy == "arbitrary") arbitrary_union(root1, root2);
        else if (strategy == "by size") union_by_size(root1, root2);
        else union_by_rank(root1, root2);
    }
    // Pomoshna funkcija za proverka na koren
    void printRoot(int x) {
        cout << "Elementot " << x << " ima koren: " << smart_find(x) << endl;
    }
};

int main() {
    // UnionFind so 10 elementi (0-9)
    UnionFind uf(10);

    // Testirame obedinuvanje
    cout << "Spojuvame 1 i 2 (by size, smart find)..." << endl;
    uf.unite(1, 2, "by size", "smart");

    cout << "Spojuvame 3 i 4 (by size, smart find)..." << endl;
    uf.unite(3, 4, "by size", "smart");

    cout << "Spojuvame 2 i 4 (sega site 1,2,3,4 treba da se vo ista grupa)..." << endl;
    uf.unite(2, 4, "by size", "smart");

    // Proverka na rezultati
    uf.printRoot(1);
    uf.printRoot(3);

    if (uf.smart_find(1) == uf.smart_find(4)) {
        cout << "1 i 4 se sega vo isto mnozhestvo" << endl;
    }

    return 0;
}
