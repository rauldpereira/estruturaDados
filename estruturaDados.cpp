#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <cctype>

using namespace std;

const int TAMANHO_TABULEIRO = 15;
const int NUM_SUBMARINOS = 4;
const int NUM_CRUZADORES = 3;
const int NUM_PORTA_AVIOES = 1;
const int NUM_ENCOURACADOS = 2;
const int NUM_HIDROVIOES = 5;
const char SUBMARINO = 'S';
const char CRUZADOR = 'C';
const char PORTA_AVIOES = 'P';
const char ENCOURACADO = 'E';
const char HIDROVIAO = 'H';

// Função para mostrar a tabela
void mostrarTabela(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], string player)
{
    cout << "Tabuleiro do " << player << ":\n";
    char letra[16] = "ABCDEFGHIJKLMNO";
    cout << "  ";
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        if (i < 9)
            cout << "0" << i + 1 << " ";
        else
            cout << i + 1 << ' ';
    }
    cout << endl;
    for (int j = 0; j < TAMANHO_TABULEIRO; j++)
    {
        cout << letra[j] << ' ';
        for (int i = 0; i < TAMANHO_TABULEIRO; i++)
        {
            if(tabuleiro[j][i] == SUBMARINO)
                cout << "SU ";
            else if(tabuleiro[j][i] == CRUZADOR)
                cout << "CR ";
            else if(tabuleiro[j][i] == PORTA_AVIOES)
                cout << "PA ";
            else if(tabuleiro[j][i] == ENCOURACADO)
                cout << "EN ";
            else if(tabuleiro[j][i] == HIDROVIAO)
                cout << "HI ";
            else if(tabuleiro[j][i] == ' ')
                cout << "[] ";
            else
                cout << tabuleiro[j][i] << " ";
        }
        cout << endl;
    }
}

// Função para determinar a direção da embarcação
bool determinarDirecao(char& direcao, char& sentido, char tipo)
{
    cout << "Escolha a direção da embarcação:\n";
    if (tipo == HIDROVIAO)
    {
        cout << "V - Vertical\n";
        cout << "H - Horizontal\n";
    }
    else
    {
        cout << "H - Horizontal\n";
        cout << "V - Vertical\n";
    }
    cin >> direcao;
    direcao = toupper(direcao);

    if (direcao == 'V')
    {
        if (tipo == HIDROVIAO)
        {
            cout << "Escolha o sentido vertical:\n";
            cout << "D - Direita\n";
            cout << "E - Esquerda\n";
        }
        else
        {
            cout << "Escolha o sentido vertical:\n";
            cout << "C - Cima\n";
            cout << "B - Baixo\n";
        }
        cin >> sentido;
        sentido = toupper(sentido);
        return (sentido == 'D' || sentido == 'E' || sentido == 'C' || sentido == 'B');
    }
    else if (direcao == 'H')
    {
        if (tipo == HIDROVIAO)
        {
            cout << "Escolha o sentido horizontal:\n";
            cout << "C - Cima\n";
            cout << "B - Baixo\n";
        }
        else
        {
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

// Função para posicionar uma embarcação
void posicionarEmbarcacao(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], char tipo, int quantidade, int jogador)
{
    for (int i = 0; i < quantidade; i++)
    {
        bool posicaoValida = false;
        while (!posicaoValida)
        {
            system("cls");
            mostrarTabela(tabuleiro, "Jogador " + to_string(jogador));

            string coordenada;
            cout << "Jogador " << jogador << " - Insira as coordenadas da "
                 << (tipo == SUBMARINO ? "submarino" : tipo == CRUZADOR ? "cruzador" : tipo == PORTA_AVIOES ? "porta-aviões" : tipo == ENCOURACADO ? "encouraçado" : "hidrovião")
                 << " " << i + 1 << " (ex: 1A): ";
            cin >> coordenada;

            int x = -1;
            int y = -1;
            // Verifica se a coordenada está no formato correto
            if (coordenada.length() < 2)
            {
                cout << "\nCoordenada inválida! Tente novamente.\n";
                cout << "Pressione Enter para continuar...";
                cin.ignore();
                cin.get();
                continue;
            }

            // Identifica a posição da letra
            int pos = 0;
            while (pos < coordenada.length() && isdigit(coordenada[pos]))
            {
                pos++;
            }

            // Verifica se a coordenada está no formato correto
            if (pos == 0 || pos == coordenada.length())
            {
                cout << "\nFormato de coordenada inválido! Tente novamente.\n";
                cout << "Pressione Enter para continuar...";
                cin.ignore();
                cin.get();
                continue;
            }

            // Trata o caso de coordenada no formato numérico + letra (ex: 3G)
            if (isdigit(coordenada[pos - 1]))
            {
                x = stoi(coordenada.substr(0, pos)) - 1;
                y = toupper(coordenada[pos]) - 'A';
            }
            // Trata o caso de coordenada no formato letra + numérico (ex: G3)
            else if (isdigit(coordenada[pos]))
            {
                y = toupper(coordenada[0]) - 'A';
                x = stoi(coordenada.substr(1, pos - 1)) - 1;
            }

            // Verifica se as coordenadas estão dentro dos limites do tabuleiro
            if (x < 0 || x >= TAMANHO_TABULEIRO || y < 0 || y >= TAMANHO_TABULEIRO)
            {
                cout << "\nCoordenada fora dos limites do tabuleiro! Tente novamente.\n";
                cout << "Pressione Enter para continuar...";
                cin.ignore();
                cin.get();
                continue;
            }

            // Verifica a direção e o sentido se for um cruzador, porta-aviões ou encouraçado
            char direcao, sentido;
            if (tipo == CRUZADOR || tipo == PORTA_AVIOES || tipo == ENCOURACADO || tipo == HIDROVIAO)
            {
                if (!determinarDirecao(direcao, sentido, tipo))
                {
                    cout << "\nDireção ou sentido inválido! Tente novamente.\n";
                    cout << "Pressione Enter para continuar...";
                    cin.ignore();
                    cin.get();
                    continue;
                }
            }

            bool espacoDisponivel = false;
            int tamanho = (tipo == SUBMARINO) ? 1 : (tipo == CRUZADOR) ? 2 : (tipo == PORTA_AVIOES) ? 5 : (tipo == ENCOURACADO) ? 4 : 3;

            if (tipo == SUBMARINO)
            {
                if (tabuleiro[y][x] == ' ')
                {
                    tabuleiro[y][x] = SUBMARINO;
                    posicaoValida = true;
                }
                else
                {
                    cout << "\nPosição inválida! Já existe uma embarcação nessa posição.\n";
                    cout << "Pressione Enter para continuar...";
                    cin.ignore();
                    cin.get();
                }
            }
            else if (tipo == CRUZADOR || tipo == PORTA_AVIOES || tipo == ENCOURACADO)
            {
                if (direcao == 'V')
                {
                    if (sentido == 'B' && y + tamanho <= TAMANHO_TABULEIRO)
                    {
                        espacoDisponivel = true;
                        for (int j = 0; j < tamanho; j++)
                        {
                            if (tabuleiro[y + j][x] != ' ')
                            {
                                espacoDisponivel = false;
                                break;
                            }
                        }
                        if (espacoDisponivel)
                        {
                            for (int j = 0; j < tamanho; j++)
                            {
                                tabuleiro[y + j][x] = tipo;
                            }
                            posicaoValida = true;
                        }
                    }
                    else if (sentido == 'C' && y - tamanho + 1 >= 0)
                    {
                        espacoDisponivel = true;
                        for (int j = 0; j < tamanho; j++)
                        {
                            if (tabuleiro[y - j][x] != ' ')
                            {
                                espacoDisponivel = false;
                                break;
                            }
                        }
                        if (espacoDisponivel)
                        {
                            for (int j = 0; j < tamanho; j++)
                            {
                                tabuleiro[y - j][x] = tipo;
                            }
                            posicaoValida = true;
                        }
                    }
                }
                else if (direcao == 'H')
                {
                    if (sentido == 'D' && x + tamanho <= TAMANHO_TABULEIRO)
                    {
                        espacoDisponivel = true;
                        for (int j = 0; j < tamanho; j++)
                        {
                            if (tabuleiro[y][x + j] != ' ')
                            {
                                espacoDisponivel = false;
                                break;
                            }
                        }
                        if (espacoDisponivel)
                        {
                            for (int j = 0; j < tamanho; j++)
                            {
                                tabuleiro[y][x + j] = tipo;
                            }
                            posicaoValida = true;
                        }
                    }
                    else if (sentido == 'E' && x - tamanho + 1 >= 0)
                    {
                        espacoDisponivel = true;
                        for (int j = 0; j < tamanho; j++)
                        {
                            if (tabuleiro[y][x - j] != ' ')
                            {
                                espacoDisponivel = false;
                                break;
                            }
                        }
                        if (espacoDisponivel)
                        {
                            for (int j = 0; j < tamanho; j++)
                            {
                                tabuleiro[y][x - j] = tipo;
                            }
                            posicaoValida = true;
                        }
                    }
                }
                else
                {
                    cout << "\nSentido inválido! Tente novamente.\n";
                    cout << "Pressione Enter para continuar...";
                    cin.ignore();
                    cin.get();
                }
            }
            else if (tipo == HIDROVIAO)
            {
                if (direcao == 'V')
                {
                    if (sentido == 'D' && x + 1 < TAMANHO_TABULEIRO && y + 1 < TAMANHO_TABULEIRO && y - 1 >= 0)
                    {
                        if (tabuleiro[y][x] == ' ' && tabuleiro[y + 1][x + 1] == ' ' && tabuleiro[y - 1][x + 1] == ' ')
                        {
                            tabuleiro[y][x] = tipo;
                            tabuleiro[y + 1][x + 1] = tipo;
                            tabuleiro[y - 1][x + 1] = tipo;
                            posicaoValida = true;
                        }
                    }
                    else if (sentido == 'E' && x - 1 >= 0 && y + 1 < TAMANHO_TABULEIRO && y - 1 >= 0)
                    {
                        if (tabuleiro[y][x] == ' ' && tabuleiro[y + 1][x - 1] == ' ' && tabuleiro[y - 1][x - 1] == ' ')
                        {
                            tabuleiro[y][x] = tipo;
                            tabuleiro[y + 1][x - 1] = tipo;
                            tabuleiro[y - 1][x - 1] = tipo;
                            posicaoValida = true;
                        }
                    }
                }
                else if (direcao == 'H')
                {
                    if (sentido == 'B' && y + 1 < TAMANHO_TABULEIRO && x + 1 < TAMANHO_TABULEIRO && x - 1 >= 0)
                    {
                        if (tabuleiro[y][x] == ' ' && tabuleiro[y + 1][x - 1] == ' ' && tabuleiro[y + 1][x + 1] == ' ')
                        {
                            tabuleiro[y][x] = tipo;
                            tabuleiro[y + 1][x - 1] = tipo;
                            tabuleiro[y + 1][x + 1] = tipo;
                            posicaoValida = true;
                        }
                    }
                    else if (sentido == 'C' && y - 1 >= 0 && x + 1 < TAMANHO_TABULEIRO && x - 1 >= 0)
                    {
                        if (tabuleiro[y][x] == ' ' && tabuleiro[y - 1][x - 1] == ' ' && tabuleiro[y - 1][x + 1] == ' ')
                        {
                            tabuleiro[y][x] = tipo;
                            tabuleiro[y - 1][x - 1] = tipo;
                            tabuleiro[y - 1][x + 1] = tipo;
                            posicaoValida = true;
                        }
                    }
                }
                else
                {
                    cout << "\nSentido inválido! Tente novamente.\n";
                    cout << "Pressione Enter para continuar...";
                    cin.ignore();
                    cin.get();
                }
            }
            else
            {
                cout << "\nTipo de embarcação inválido! Tente novamente.\n";
                cout << "Pressione Enter para continuar...";
                cin.ignore();
                cin.get();
            }

            if (!posicaoValida)
            {
                cout << "\nNão foi possível posicionar a embarcação. Tente novamente.\n";
                cout << "Pressione Enter para continuar...";
                cin.ignore();
                cin.get();
            }
        }
    }
}

void playerVsPlayer()
{
    char tabuleiro1[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    char tabuleiro2[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa os tabuleiros com espaços vazios
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
        {
            tabuleiro1[i][j] = ' ';
            tabuleiro2[i][j] = ' ';
        }
    }

    cout << "Jogo Batalha Naval - Jogador 1\n";
    cout << "Coloque suas embarcações:\n";

    // Posiciona os submarinos, cruzadores, porta-aviões e hidroviões para o Jogador 1
    posicionarEmbarcacao(tabuleiro1, SUBMARINO, NUM_SUBMARINOS, 1);
    posicionarEmbarcacao(tabuleiro1, CRUZADOR, NUM_CRUZADORES, 1);
    posicionarEmbarcacao(tabuleiro1, ENCOURACADO, NUM_ENCOURACADOS, 1);
    posicionarEmbarcacao(tabuleiro1, PORTA_AVIOES, NUM_PORTA_AVIOES, 1);
    posicionarEmbarcacao(tabuleiro1, HIDROVIAO, NUM_HIDROVIOES, 1);

    system("cls");
    mostrarTabela(tabuleiro1, "Jogador 1");
    cout << "Pressione Enter para continuar...";
    cin.ignore();
    cin.get();

    system("cls");
    cout << "Jogo Batalha Naval - Jogador 2\n";
    cout << "Coloque suas embarcações:\n";

    // Posiciona os submarinos, cruzadores, porta-aviões e hidroviões para o Jogador 2
    posicionarEmbarcacao(tabuleiro2, SUBMARINO, NUM_SUBMARINOS, 2);
    posicionarEmbarcacao(tabuleiro2, CRUZADOR, NUM_CRUZADORES, 2);
    posicionarEmbarcacao(tabuleiro2, ENCOURACADO, NUM_ENCOURACADOS, 2);
    posicionarEmbarcacao(tabuleiro2, PORTA_AVIOES, NUM_PORTA_AVIOES, 2);
    posicionarEmbarcacao(tabuleiro2, HIDROVIAO, NUM_HIDROVIOES, 2);

    system("cls");
    mostrarTabela(tabuleiro1, "Jogador 1");
    mostrarTabela(tabuleiro2, "Jogador 2");

    cout << "Pressione Enter para encerrar...";
    cin.ignore();
    cin.get();
}

void batalhaNaval()
{
    cout << "Batalha Naval\n";
    int op = 0;
    while (op != 4)
    {
        system("cls");

        cout << "Qual modo deseja jogar? \n\
1 - Player vs Player\n\
2 - Player vs CPU \n\
3 - CPU vs CPU\n\
4 - Sair.\n";
        cin >> op;

        switch (op)
        {
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

void matrizesVetores()
{
    cout << "Matrizes e Vetores\n";
    int op = 0;

    while (op != 5)
    {
        system("cls");

        cout << "Qual modo deseja jogar? \n\
1 - Batalha Naval\n\
2 - P2 \n\
3 - P3\n\
4 - P4 \n\
5 - Sair.\n";
        cin >> op;

        switch (op)
        {
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

int main(void)
{
    setlocale(LC_ALL, "Portuguese");

    int op = 0;

    while (op != 5)
    {
        system("cls");

        cout << "Escolha uma opção: \n\
1 - P1 - Matrizes/vetores\n\
2 - P2 \n\
3 - P3 \n\
4 - P4 \n\
5 - Sair\n";

        cin >> op;

        switch (op)
        {
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
