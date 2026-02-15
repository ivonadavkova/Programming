//union find 1998. GCD Sort of an Array

#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Klasa za Union-Find struktura
class UnionFind {
public:
    vector<int> parent;
    // Konstruktor: n elementi se inicijaliziraat kako posebni grupi
    UnionFind(int n) {
        parent.resize(n);
        // iota ja polni nizata so 0, 1, 2... n-1 (sekoj e sam svoj gazda)
        iota(parent.begin(), parent.end(), 0);
    }
    // Funkcija koja naogja koj e glavniot (koren) na grupata
    int find(int i) {
        if (parent[i] == i) return i;
        // Path compression: direktno go povrzuvame jazelot so korenot za pobrza proverka sledniot pat
        return parent[i] = find(parent[i]);
    }
    // Funkcija koja spojuva dve grupi vo edna
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) parent[root_i] = root_j;
    }
};

class Solution {
public:
    bool gcdSort(vector<int>& nums) {
        // Go naogjame najgolemiot broj vo nizata za da znaeme kolkava UnionFind struktura ni treba
        int max_num = *max_element(nums.begin(), nums.end());
        UnionFind uf(max_num + 1);

        //Povrzuvanje na broevite preku nivnite prosti faktori
        for (int x : nums) {
            int temp = x;
            // Go delime brojot so site mozni prosti faktori pochuvajki od 2
            for (int d = 2; d * d <= temp; d++) {
                if (temp % d == 0) {
                    // Ako 'd' e faktor na 'x', gi spojuvame brojot i faktorot vo ista grupa
                    uf.unite(x, d);
                    // Go vadime faktorot 'd' celosno od brojot
                    while (temp % d == 0) temp /= d;
                }
            }
            // Ako ostane broj pogolem od 1, toj e posleden prost faktor, go spojuvame i nego
            if (temp > 1) uf.unite(x, temp);
        }

        //Kreirame kopija od nizata i ja sortirame za da znaeme kade TREBA da stojat broevite
        vector<int> sorted_nums = nums;
        sort(sorted_nums.begin(), sorted_nums.end());

        //Proverka dali broevite mozat da stignat do svojata sortirana pozicija
        for (int i = 0; i < nums.size(); i++) {
            // Ako brojot na pozicija 'i' ne e ist kako vo sortiratnata niza...
            if (nums[i] != sorted_nums[i]) {
                // Ako se vo ista grupa, znachi postoi pat od zameni (swaps) megu niv.
                if (uf.find(nums[i]) != uf.find(sorted_nums[i])) {
                    // Ako nemaat ist koren, ne mozat nikako da si gi zamenat mestata i nemozhno e da se sortira
                    return false;
                }
            }
        }
        return true;
    }
};
