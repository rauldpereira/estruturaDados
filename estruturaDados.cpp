#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <locale.h>

using namespace std;

const int TAMANHO_TABULEIRO = 15;

class Embarcacao {
public:
    char tipo;
    int tamanho;

    Embarcacao(char t, int tam) : tipo(t), tamanho(tam) {}
};

class Tabuleiro {
private:
    vector<vector<char>> tabuleiro;

public:
    Tabuleiro() {
        tabuleiro.resize(TAMANHO_TABULEIRO, vector<char>(TAMANHO_TABULEIRO, ' '));
    }

    void mostrarTabela(string player) {
        cout << "Tabuleiro do " << player << ":\n";
        char letra[16] = "ABCDEFGHIJKLMNO";
        cout << "  ";
        for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
            cout << (i < 9 ? "0" : "") << i + 1 << " ";
        }
        cout << endl;

        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            cout << letra[j] << ' ';
            for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
                cout << (tabuleiro[j][i] == ' ' ? "[] " : string(1, tabuleiro[j][i]) + " ");
            }
            cout << endl;
        }
    }

    bool posicionarEmbarcacao(int x, int y, char direcao, char sentido, Embarcacao& embarcacao) {
        if (direcao == 'V') {
            if (sentido == 'B') {
                if (y + embarcacao.tamanho > TAMANHO_TABULEIRO) return false;
                for (int j = 0; j < embarcacao.tamanho; j++) {
                    if (tabuleiro[y + j][x] != ' ') return false;
                }
                for (int j = 0; j < embarcacao.tamanho; j++) {
                    tabuleiro[y + j][x] = embarcacao.tipo;
                }
            } else if (sentido == 'C') {
                if (y - embarcacao.tamanho + 1 < 0) return false;
                for (int j = 0; j < embarcacao.tamanho; j++) {
                    if (tabuleiro[y - j][x] != ' ') return false;
                }
                for (int j = 0; j < embarcacao.tamanho; j++) {
                    tabuleiro[y - j][x] = embarcacao.tipo;
                }
            }
        } else if (direcao == 'H') {
            if (sentido == 'D') {
                if (x + embarcacao.tamanho > TAMANHO_TABULEIRO) return false;
                for (int j = 0; j < embarcacao.tamanho; j++) {
                    if (tabuleiro[y][x + j] != ' ') return false;
                }
                for (int j = 0; j < embarcacao.tamanho; j++) {
                    tabuleiro[y][x + j] = embarcacao.tipo;
                }
            } else if (sentido == 'E') {
                if (x - embarcacao.tamanho + 1 < 0) return false;
                for (int j = 0; j < embarcacao.tamanho; j++) {
                    if (tabuleiro[y][x - j] != ' ') return false;
                }
                for (int j = 0; j < embarcacao.tamanho; j++) {
                    tabuleiro[y][x - j] = embarcacao.tipo;
                }
            }
        }
        return true;
    }

};

class Jogador {
private:
    string nome;
    Tabuleiro tabuleiro;
    vector<Embarcacao> embarcacoes;

public:
    Jogador(string n) : nome(n) {
        embarcacoes.push_back(Embarcacao('S', 1)); // Submarino
        embarcacoes.push_back(Embarcacao('C', 2)); // Cruzador
        embarcacoes.push_back(Embarcacao('P', 5)); // Porta-Aviões
        embarcacoes.push_back(Embarcacao('E', 4)); // Encouraçado
        embarcacoes.push_back(Embarcacao('H', 3)); // Hidroavião
    }

    void colocarEmbarcacoes() {
        for (auto& embarcacao : embarcacoes) {
            bool posicionado = false;
            while (!posicionado) {
                char direcao, sentido;
                int x, y;

                cout << "Coloque sua " << embarcacao.tipo << " (Tamanho: " << embarcacao.tamanho << ")\n";
                cout << "Coordenadas (ex: 3A): ";
                string coordenada;
                cin >> coordenada;

                if (coordenada.length() < 2 || !isdigit(coordenada[0]) || !isalpha(coordenada[1])) {
                    cout << "Coordenada inválida! Tente novamente.\n";
                    continue;
                }

                y = toupper(coordenada[1]) - 'A';
                x = stoi(coordenada.substr(0, coordenada.length() - 1)) - 1;

                cout << "Escolha a direção (H - Horizontal, V - Vertical): ";
                cin >> direcao;
                direcao = toupper(direcao);

                cout << "Escolha o sentido (D - Direita, E - Esquerda, C - Cima, B - Baixo): ";
                cin >> sentido;
                sentido = toupper(sentido);

                posicionado = tabuleiro.posicionarEmbarcacao(x, y, direcao, sentido, embarcacao);
                if (!posicionado) {
                    cout << "Posição inválida! Tente novamente.\n";
                }
            }
        }
    }

    void mostrarTabuleiro() {
        tabuleiro.mostrarTabela(nome);
    }
};

void playerVsPlayer() {
    Jogador jogador1("Jogador 1");
    Jogador jogador2("Jogador 2");

    cout << "Jogo Batalha Naval - Jogador 1\n";
    jogador1.colocarEmbarcacoes();

    system("cls");
    jogador1.mostrarTabuleiro();
    cout << "Pressione Enter para continuar...";
    cin.ignore();
    cin.get();

    system("cls");
    cout << "Jogo Batalha Naval - Jogador 2\n";
    jogador2.colocarEmbarcacoes();

    system("cls");
    jogador1.mostrarTabuleiro();
    jogador2.mostrarTabuleiro();

    cout << "Pressione Enter para encerrar...";
    cin.ignore();
    cin.get();
}

void batalhaNaval() {
    cout << "Batalha Naval\n";
    int op = 0;
    while (op != 4) {
        system("cls");

        cout << "Qual modo deseja jogar? \n\
1 - Player vs Player\n\
2 - Player vs CPU \n\
3 - CPU vs CPU\n\
4 - Sair.\n";
        cin >> op;

        switch (op) {
        case 1:
            playerVsPlayer();
            break;
        case 2:
            cout << "Player vs CPU\n";
            break;
        case 3:
            cout << "CPU vs CPU\n";
            break;
        case 4:
            cout << "Saindo...";
            break;
        default:
            cout << "Opção Inválida.\n";
            break;
        }
    }
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    int op = 0;

    while (op != 5) {
        system("cls");
        cout << "Escolha uma opção: \n\
1 - Batalha Naval\n\
2 - P2 \n\
3 - P3 \n\
4 - P4 \n\
5 - Sair\n";
        cin >> op;

        switch (op) {
        case 1:
            batalhaNaval();
            break;
        case 2:
            cout << "oi\n";
            break;
        case 3:
            cout << "oi\n";
            break;
        case 4:
            cout << "oi\n";
            break;
        case 5:
            cout << "Saindo...";
            break;
        default:
            cout << "Opção Inválida.\n";
            break;
        }
    }
    return 0;
}
