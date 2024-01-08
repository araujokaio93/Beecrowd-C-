#include <iostream>
#include <vector>
#include <climits>
#include <list>
#include <utility>

using namespace std;

class KnightMovesSolver {
public:
    KnightMovesSolver() : rows(8), cols(8) {
        initializeKnightMoves();
    }

    ~KnightMovesSolver() {
        // Adicione código de limpeza, se necessário
    }

    int findShortestPath(const string& start, const string& end) {
        pair<int, int> startCoords = getCoordinates(start);
        pair<int, int> endCoords = getCoordinates(end);

        vector<int> dist(rows * cols, INT_MAX);
        dist[startCoords.first * cols + startCoords.second] = 0;

        if (bellmanFord(dist)) {
            return dist[endCoords.first * cols + endCoords.second];
        } else {
            // Se houver ciclo de peso negativo, a solução é inválida
            return -1;
        }
    }

    // Métodos getters e setters, se necessário
    int getRows() const {
        return rows;
    }

    void setRows(int newRows) {
        rows = newRows;
    }

    int getCols() const {
        return cols;
    }

    void setCols(int newCols) {
        cols = newCols;
    }

private:
    int rows;
    int cols;
    vector<list<pair<int, int>>> adjacencyList;  // Lista de adjacência

    void initializeKnightMoves() {
        vector<pair<int, int>> possibleMoves = { {-2, -1}, {-1, -2}, {1, -2}, {2, -1},
                                                 {2, 1}, {1, 2}, {-1, 2}, {-2, 1} };

        adjacencyList.resize(rows * cols);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                for (const auto& move : possibleMoves) {
                    int ni = i + move.first;
                    int nj = j + move.second;

                    if (isValid(ni, nj)) {
                        adjacencyList[i * cols + j].emplace_back(ni * cols + nj, 1);
                    }
                }
            }
        }
    }

    bool isValid(int i, int j) const {
        return i >= 0 && i < rows && j >= 0 && j < cols;
    }

    pair<int, int> getCoordinates(const string& square) const {
        int col = square[0] - 'a';
        int row = 8 - (square[1] - '0');
        return make_pair(row, col);
    }

    void relax(int u, int v, vector<int>& dist) {
        if (dist[u] != INT_MAX && dist[u] + 1 < dist[v]) {
            dist[v] = dist[u] + 1;
        }
    }

    bool bellmanFord(vector<int>& dist) {
        for (int i = 1; i <= rows * cols - 1; ++i) {
            for (int u = 0; u < rows * cols; ++u) {
                for (const auto& neighbor : adjacencyList[u]) {
                    int v = neighbor.first;
                    relax(u, v, dist);
                }
            }
        }

        // Verifica se há ciclo de peso negativo
        for (int u = 0; u < rows * cols; ++u) {
            for (const auto& neighbor : adjacencyList[u]) {
                int v = neighbor.first;
                if (dist[v] > dist[u] + 1) {
                    return false;
                }
            }
        }

        return true;
    }
};

int main() {
    KnightMovesSolver solver;

    string start, end;
    while (cin >> start >> end) {
        int moves = solver.findShortestPath(start, end);
        cout << "To get from " << start << " to " << end << " takes " << moves << " knight moves." << endl;
    }

    return 0;
}
