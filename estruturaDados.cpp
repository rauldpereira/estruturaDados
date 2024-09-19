#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <cctype>

using namespace std;

const int TAMANHO_TABULEIRO = 15;
const char VAZIO = ' ';

// Classe base para embarcações
class Embarcacao {
public:
    char tipo;
    int tamanho;
    Embarcacao(char t, int tam) : tipo(t), tamanho(tam) {}
    virtual ~Embarcacao() {}
};

// Classes derivadas para tipos específicos de embarcações
class Submarino : public Embarcacao {
public:
    Submarino() : Embarcacao('S', 1) {}
};

class Cruzador : public Embarcacao {
public:
    Cruzador() : Embarcacao('C', 2) {}
};

class PortaAvioes : public Embarcacao {
public:
    PortaAvioes() : Embarcacao('P', 5) {}
};

class Encouracado : public Embarcacao {
public:
    Encouracado() : Embarcacao('E', 4) {}
};

class Hidroaviao : public Embarcacao {
public:
    Hidroaviao() : Embarcacao('H', 3) {}
};

void mostrarTabela(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], string player) {
    cout << "Tabuleiro do " << player << ":\n";
    char letra[16] = "ABCDEFGHIJKLMNO";
    cout << "  ";
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        if (i < 9)
            cout << "0" << i + 1 << " ";
        else
            cout << i + 1 << ' ';
    }
    cout << endl;
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        cout << letra[j] << ' ';
        for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
            switch (tabuleiro[j][i]) {
                case 'S': cout << "SU "; break;
                case 'C': cout << "CR "; break;
                case 'P': cout << "PA "; break;
                case 'E': cout << "EN "; break;
                case 'H': cout << "HI "; break;
                case ' ': cout << "[] "; break;
                default: cout << tabuleiro[j][i] << " ";
            }
        }
        cout << endl;
    }
}

bool determinarDirecao(char& direcao, char& sentido, char tipo) {
    cout << "Escolha a direção da embarcação:\n";
    if (tipo == 'H') {
        cout << "V - Vertical\n";
        cout << "H - Horizontal\n";
    } else {
        cout << "H - Horizontal\n";
        cout << "V - Vertical\n";
    }
    cin >> direcao;
    direcao = toupper(direcao);

    if (direcao == 'V') {
        if (tipo == 'H') {
            cout << "Escolha o sentido vertical:\n";
            cout << "D - Direita\n";
            cout << "E - Esquerda\n";
        } else {
            cout << "Escolha o sentido vertical:\n";
            cout << "C - Cima\n";
            cout << "B - Baixo\n";
        }
        cin >> sentido;
        sentido = toupper(sentido);
        return (sentido == 'D' || sentido == 'E' || sentido == 'C' || sentido == 'B');
    } else if (direcao == 'H') {
        if (tipo == 'H') {
            cout << "Escolha o sentido horizontal:\n";
            cout << "C - Cima\n";
            cout << "B - Baixo\n";
        } else {
            cout << "Escolha o sentido horizontal:\n";
            cout << "D - Direita\n";
            cout << "E - Esquerda\n";
        }
        cin >> sentido;
        sentido = toupper(sentido);
        return (sentido == 'D' || sentido == 'E' || sentido == 'C' || sentido == 'B');
    }

    return false;
}

bool verificarEspaco(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int x, int y, int tamanho, char tipo, char direcao, char sentido) {
    bool espacoDisponivel = false;

    if (direcao == 'V') {
        if (sentido == 'B' && y + tamanho <= TAMANHO_TABULEIRO) {
            espacoDisponivel = true;
            for (int j = 0; j < tamanho; j++) {
                if (tabuleiro[y + j][x] != ' ') {
                    espacoDisponivel = false;
                    break;
                }
            }
        } else if (sentido == 'C' && y - tamanho + 1 >= 0) {
            espacoDisponivel = true;
            for (int j = 0; j < tamanho; j++) {
                if (tabuleiro[y - j][x] != ' ') {
                    espacoDisponivel = false;
                    break;
                }
            }
        }
    } else if (direcao == 'H') {
        if (sentido == 'D' && x + tamanho <= TAMANHO_TABULEIRO) {
            espacoDisponivel = true;
            for (int j = 0; j < tamanho; j++) {
                if (tabuleiro[y][x + j] != ' ') {
                    espacoDisponivel = false;
                    break;
                }
            }
        } else if (sentido == 'E' && x - tamanho + 1 >= 0) {
            espacoDisponivel = true;
            for (int j = 0; j < tamanho; j++) {
                if (tabuleiro[y][x - j] != ' ') {
                    espacoDisponivel = false;
                    break;
                }
            }
        }
    }

    return espacoDisponivel;
}

void posicionarEmbarcacao(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], Embarcacao* embarcacao, int quantidade, int jogador) {
    for (int i = 0; i < quantidade; i++) {
        bool posicaoValida = false;
        while (!posicaoValida) {
            system("cls");
            mostrarTabela(tabuleiro, "Jogador " + to_string(jogador));

            string coordenada;
            cout << "Jogador " << jogador << " - Insira as coordenadas da "
                 << (embarcacao->tipo == 'S' ? "submarino" : embarcacao->tipo == 'C' ? "cruzador" : embarcacao->tipo == 'P' ? "porta-aviões" : embarcacao->tipo == 'E' ? "encouraçado" : "hidroavião")
                 << " " << i + 1 << " (ex: 1A): ";
            cin >> coordenada;

            int x = -1;
            int y = -1;
            // Verifica se a coordenada está no formato correto
            if (coordenada.length() < 2) {
                cout << "\nCoordenada inválida! Tente novamente.\n";
                cout << "Pressione Enter para continuar...";
                cin.ignore();
                cin.get();
                continue;
            }

            // Identifica a posição da letra
            int pos = 0;
            while (pos < coordenada.length() && isdigit(coordenada[pos])) {
                pos++;
            }

            // Verifica se a coordenada está no formato correto
            if (pos == 0 || pos == coordenada.length()) {
                cout << "\nFormato de coordenada inválido! Tente novamente.\n";
                cout << "Pressione Enter para continuar...";
                cin.ignore();
                cin.get();
                continue;
            }

            // Trata o caso de coordenada no formato numérico + letra (ex: 3G)
            if (isdigit(coordenada[pos - 1])) {
                x = stoi(coordenada.substr(0, pos)) - 1;
                y = toupper(coordenada[pos]) - 'A';
            }
            // Trata o caso de coordenada no formato letra + numérico (ex: G3)
            else if (isdigit(coordenada[pos])) {
                y = toupper(coordenada[0]) - 'A';
                x = stoi(coordenada.substr(1, pos - 1)) - 1;
            }

            // Verifica se as coordenadas estão dentro dos limites do tabuleiro
            if (x < 0 || x >= TAMANHO_TABULEIRO || y < 0 || y >= TAMANHO_TABULEIRO) {
                cout << "\nCoordenada fora dos limites do tabuleiro! Tente novamente.\n";
                cout << "Pressione Enter para continuar...";
                cin.ignore();
                cin.get();
                continue;
            }

            char direcao;
            char sentido;
            if (!determinarDirecao(direcao, sentido, embarcacao->tipo)) {
                cout << "\nDireção ou sentido inválidos! Tente novamente.\n";
                cout << "Pressione Enter para continuar...";
                cin.ignore();
                cin.get();
                continue;
            }

            // Verifica se o espaço é adequado para posicionar a embarcação
            if (verificarEspaco(tabuleiro, x, y, embarcacao->tamanho, embarcacao->tipo, direcao, sentido)) {
                posicaoValida = true;

                if (direcao == 'V') {
                    if (sentido == 'B') {
                        for (int j = 0; j < embarcacao->tamanho; j++) {
                            tabuleiro[y + j][x] = embarcacao->tipo;
                        }
                    } else if (sentido == 'C') {
                        for (int j = 0; j < embarcacao->tamanho; j++) {
                            tabuleiro[y - j][x] = embarcacao->tipo;
                        }
                    }
                } else if (direcao == 'H') {
                    if (sentido == 'D') {
                        for (int j = 0; j < embarcacao->tamanho; j++) {
                            tabuleiro[y][x + j] = embarcacao->tipo;
                        }
                    } else if (sentido == 'E') {
                        for (int j = 0; j < embarcacao->tamanho; j++) {
                            tabuleiro[y][x - j] = embarcacao->tipo;
                        }
                    }
                }
            } else {
                cout << "\nEspaço inválido para a embarcação! Tente novamente.\n";
                cout << "Pressione Enter para continuar...";
                cin.ignore();
                cin.get();
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    Embarcacao* embarcacoes[5] = { new Submarino(), new Cruzador(), new PortaAvioes(), new Encouracado(), new Hidroaviao() };

    // Inicializa o tabuleiro com espaços vazios
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = VAZIO;
        }
    }

    for (int i = 0; i < 5; i++) {
        posicionarEmbarcacao(tabuleiro, embarcacoes[i], 1, 1);
    }

    mostrarTabela(tabuleiro, "Jogador 1");


    for (int i = 0; i < 5; i++) {
        delete embarcacoes[i];
    }

    return 0;
}
