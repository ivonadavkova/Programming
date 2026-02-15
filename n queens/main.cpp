#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Kade moze da se stavi kralica bez da bide napadnata
bool isSafe(vector<int>& board, int row, int col) {
    // Proveruvame so site prethodno postaveni kralici
    for (int i = 0; i < row; i++) {
        int otherCol = board[i];
        if (otherCol == col) return false;
        if (abs(i - row) == abs(otherCol - col)) return false;
    }
    return true;
}

// Brute Force funkcija
void solve(int n, int row, vector<int>& board, vector<vector<int>>& results) {
    // Ako stignavme do posledniot red, sme nashle celosno reshenie
    if (row == n) {
        results.push_back(board);
        return;
    }

    // Probuvame da ja stavime kralicata vo sekoja kolona od redot
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            solve(n, row + 1, board, results);
        }
    }
}

int main() {
    int n;
    cin>>n;
    vector<vector<int>> results;
    vector<int> board(n); // board[i] = kolona vo koja se naogja kralicata vo red i

    solve(n, 0, board, results);

    if (results.empty()) {
        cout << "Nema reshenie" << n << endl;
    } else {
        cout << results.size()<< endl;
        for (auto res : results) {
            cout << "[ ";
            for (int col : res) cout << col << " ";
            cout << "]" << endl;
        }
    }

    return 0;
}
