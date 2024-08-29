#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <cctype>

using namespace std;

const int TAMANHO_TABULEIRO = 15;
const int NUM_SUBMARINOS = 4;

void mostrarTabela(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], string player) {
    system("cls");

    char letra[16] = "ABCDEFGHIJKLMNO";
    cout << "Tabuleiro do " << player << ":\n";
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
            if(tabuleiro[j][i] == 'S')
                cout << "SU ";
            else if(tabuleiro[j][i] == ' ')
                cout << "[] ";
            else
                cout << tabuleiro[j][i] << " ";
        }
        cout << endl;
    }
}

void playerVsPlayer(){

    char tabuleiro1[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    char tabuleiro2[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicialização dos tabuleiros
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro1[i][j] = ' ';
            tabuleiro2[i][j] = ' ';
        }
    }

    int submarinos[NUM_SUBMARINOS][2];

    // Jogador 1 submarinos
    for (int i = 0; i < NUM_SUBMARINOS; i++) {
        bool posicaoValida = false;
        while (!posicaoValida) {
            mostrarTabela(tabuleiro1, "Jogador 1");
            string coordenada;
            cout << "Jogador 1, insira as coordenadas do submarino " << i + 1 << " (ex: 1A): ";
            cin >> coordenada;

            int x = stoi(coordenada.substr(0, coordenada.size() - 1)) - 1;
            char letra = coordenada.back();
            letra = toupper(letra);
            int y = letra - 'A';

            if (tabuleiro1[y][x] == ' ') {
                submarinos[i][0] = x;
                submarinos[i][1] = y;
                tabuleiro1[y][x] = 'S';
                posicaoValida = true;
            } else {
                cout << "Posição inválida! Já existe um submarino nessa posição." << endl;
                cin.get();
                cin.get(); 
            }
        }
    }

    // Jogador 2 submarinos
    for (int i = 0; i < NUM_SUBMARINOS; i++) {
        bool posicaoValida = false;
        while (!posicaoValida) {
            mostrarTabela(tabuleiro2, "Jogador 2");
            string coordenada;
            cout << "Jogador 2, insira as coordenadas do submarino " << i + 1 << " (ex: 1A): ";
            cin >> coordenada;

            int x = stoi(coordenada.substr(0, coordenada.size() - 1)) - 1;
            char letra = coordenada.back();
            letra = toupper(letra);  
            int y = letra - 'A';

            if (tabuleiro2[y][x] == ' ') {
                submarinos[i][0] = x;
                submarinos[i][1] = y;
                tabuleiro2[y][x] = 'S';
                posicaoValida = true;
            } else {
                cout << "Posição inválida! Já existe um submarino nessa posição." << endl;
                cin.get();
                cin.get(); 
            }
        }
    }

    mostrarTabela(tabuleiro1, "Jogador 1");
    mostrarTabela(tabuleiro2, "Jogador 2");

    cout << "Pressione Enter para continuar...";
    cin.get();
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
                cout << "Player vs Player\n";
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


void matrizesVetores() {
    cout << "Matrizes e Vetores\n";
    int op = 0;

    while (op != 5) {
        system("cls");

        cout << "Qual modo deseja jogar? \n\
1 - Batalha Naval\n\
2 - P2 \n\
3 - P3\n\
4 - P4 \n\
5 - Sair.\n";
        cin >> op;

        switch (op) {
            case 1:
                cout << "Batalha Naval\n";
                batalhaNaval();
                break;
            case 2:
                cout << "P2\n";
                break;
            case 3:
                cout << "P3\n";
                break;
            case 4:
                cout << "P4\n";
                break;
            case 5:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção Inválida.\n";
                break;
        }
    }
}

int main(void) {
    setlocale(LC_ALL, "pt-BR.UTF-8");

    int op = 0;

    while (op != 5) {
        system("cls");

        cout << "Escolha uma opção: \n\
1 - P1 - Matrizes/vetores\n\
2 - P2 \n\
3 - P3 \n\
4 - P4 \n\
5 - Sair\n";

        cin >> op;

        switch (op) {
            case 1:
                matrizesVetores();
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
