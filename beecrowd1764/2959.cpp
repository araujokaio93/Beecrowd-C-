#include <iostream>
#include <vector>
#include <climits>

class CityNavigation {
private:
    int numLocations;
    std::vector<std::vector<int>> connections;

public:
    // Constructor
    CityNavigation(int N) : numLocations(N), connections(N, std::vector<int>(N, INT_MAX / 2)) {
        for (int i = 0; i < N; ++i) {
            connections[i][i] = 0;
        }
    }

    // Destructor
    ~CityNavigation() {
        // Destructor code, if needed
    }

    // Copy Constructor
    CityNavigation(const CityNavigation &other) {
        numLocations = other.numLocations;
        connections = other.connections;
    }

    // Copy Assignment Operator
    CityNavigation& operator=(const CityNavigation &other) {
        if (this != &other) {
            numLocations = other.numLocations;
            connections = other.connections;
        }
        return *this;
    }

    void addConnection(int A, int B) {
        connections[A - 1][B - 1] = 1;
        connections[B - 1][A - 1] = 1;
    }

    void floydWarshall() {
        for (int k = 0; k < numLocations; ++k) {
            for (int i = 0; i < numLocations; ++i) {
                for (int j = 0; j < numLocations; ++j) {
                    connections[i][j] = std::min(connections[i][j], connections[i][k] + connections[k][j]);
                }
            }
        }
    }

    bool checkConnection(int K, int L) const {
        return connections[K - 1][L - 1] != INT_MAX / 2;
    }

    // Getters
    int getNumLocations() const {
        return numLocations;
    }

    const std::vector<std::vector<int>>& getConnections() const {
        return connections;
    }

    // Setters
    void setNumLocations(int N) {
        numLocations = N;
        connections.resize(N, std::vector<int>(N, INT_MAX / 2));
        for (int i = 0; i < N; ++i) {
            connections[i][i] = 0;
        }
    }

    void setConnections(const std::vector<std::vector<int>>& newConnections) {
        connections = newConnections;
    }
};

int main() {
    int N, M, P;
    std::cin >> N >> M >> P;

    CityNavigation city(N);

    for (int i = 0; i < M; ++i) {
        int A, B;
        std::cin >> A >> B;
        city.addConnection(A, B);
    }

    city.floydWarshall();

    for (int i = 0; i < P; ++i) {
        int K, L;
        std::cin >> K >> L;

        if (city.checkConnection(K, L)) {
            std::cout << "Lets que lets" << std::endl;
        } else {
            std::cout << "Deu ruim" << std::endl;
        }
    }

    return 0;
}
