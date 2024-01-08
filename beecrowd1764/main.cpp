#include <iostream>
#include <vector>
#include <algorithm>

class MapaNatal {
public:
    int quantidadeCidades;
    std::vector<std::vector<int>> conexoes;

    // Construtor padrão
    MapaNatal() : quantidadeCidades(0), conexoes() {}

    // Construtor com parâmetros
    MapaNatal(int cidades) : quantidadeCidades(cidades), conexoes() {}

    // Destrutor
    ~MapaNatal() {}

    // Getter
    int getQuantidadeCidades() const {
        return quantidadeCidades;
    }

    // Setter
    void setQuantidadeCidades(int cidades) {
        quantidadeCidades = cidades;
    }

    // Adiciona uma conexão ao mapa
    void AdicionarConexao(int origem, int destino, int distancia) {
        conexoes.push_back({origem, destino, distancia});
    }
};

class NoelNavegador {
public:
    // Construtor padrão
    NoelNavegador() {}

    // Destrutor
    ~NoelNavegador() {}

    // Getter e Setter não são necessários para as variáveis locais

    std::vector<std::vector<int>> ExplorarMapaOtimo(MapaNatal& mapa) {
        std::sort(mapa.conexoes.begin(), mapa.conexoes.end(), [](const auto& a, const auto& b) {
            return a[2] < b[2];
        });

        std::vector<int> navegador(mapa.getQuantidadeCidades());
        std::vector<int> expedicao(mapa.getQuantidadeCidades(), 0);

        for (int cidade = 0; cidade < mapa.getQuantidadeCidades(); ++cidade) {
            navegador[cidade] = cidade;
        }

        std::vector<std::vector<int>> rota;

        for (const auto& conexao : mapa.conexoes) {
            int origem = conexao[0];
            int destino = conexao[1];
            int distancia = conexao[2];

            int x = DescobrirNavegador(navegador, origem);
            int y = DescobrirNavegador(navegador, destino);

            if (x != y) {
                rota.push_back({origem, destino, distancia});
                EstabelecerExpedicao(navegador, expedicao, x, y);
            }
        }

        return rota;
    }

private:
    int DescobrirNavegador(std::vector<int>& navegador, int i) {
        if (navegador[i] == i) {
            return i;
        }
        return DescobrirNavegador(navegador, navegador[i]);
    }

    void EstabelecerExpedicao(std::vector<int>& navegador, std::vector<int>& expedicao, int x, int y) {
        int xLider = DescobrirNavegador(navegador, x);
        int yLider = DescobrirNavegador(navegador, y);

        if (expedicao[xLider] < expedicao[yLider]) {
            navegador[xLider] = yLider;
        } else if (expedicao[xLider] > expedicao[yLider]) {
            navegador[yLider] = xLider;
        } else {
            navegador[yLider] = xLider;
            expedicao[xLider]++;
        }
    }
};

int main() {
    while (true) {
        int numCidades, numCaminhos;
        std::cin >> numCidades >> numCaminhos;

        if (numCidades == 0 && numCaminhos == 0) {
            break;  // Fim da entrada
        }

        // Utilizando construtores e setters
        MapaNatal mapaNatal(numCidades);
        mapaNatal.setQuantidadeCidades(numCidades);

        for (int i = 0; i < numCaminhos; ++i) {
            int origem, destino, distancia;
            std::cin >> origem >> destino >> distancia;
            mapaNatal.AdicionarConexao(origem, destino, distancia);
        }

        NoelNavegador noelNavegador;

        // Utilizando getters
        auto rotaOtima = noelNavegador.ExplorarMapaOtimo(mapaNatal);

        int distanciaTotal = 0;
        for (const auto& passo : rotaOtima) {
            distanciaTotal += passo[2];
        }

        std::cout << distanciaTotal << std::endl;
    }

    return 0;
}
