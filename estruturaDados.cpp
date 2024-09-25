#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

const int TAMANHO_TABULEIRO = 15;
const char VAZIO = ' ';

// Classe base para embarcações
class Embarcacao
{
public:
    char tipo;
    int tamanho;
    Embarcacao(char t, int tam) : tipo(t), tamanho(tam) {}
    virtual ~Embarcacao() {}
};

// Classes derivadas para tipos específicos de embarcações
class Submarino : public Embarcacao
{
public:
    Submarino() : Embarcacao('S', 1) {}
};

class Cruzador : public Embarcacao
{
public:
    Cruzador() : Embarcacao('C', 2) {}
};

class PortaAvioes : public Embarcacao
{
public:
    PortaAvioes() : Embarcacao('P', 5) {}
};

class Encouracado : public Embarcacao
{
public:
    Encouracado() : Embarcacao('E', 4) {}
};

class Hidroaviao : public Embarcacao
{
public:
    Hidroaviao() : Embarcacao('H', 3) {}
};

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
            switch (tabuleiro[j][i])
            {
            case 'S':
                cout << "SU ";
                break;
            case 'C':
                cout << "CR ";
                break;
            case 'P':
                cout << "PA ";
                break;
            case 'E':
                cout << "EN ";
                break;
            case 'H':
                cout << "HI ";
                break;
            case ' ':
                cout << "[] ";
                break;
            default:
                cout << tabuleiro[j][i] << " ";
            }
        }
        cout << endl;
    }
}

bool determinarDirecao(char& direcao, char& sentido, char tipo)
{
    cout << "Escolha a direção da embarcação:\n";
    if (tipo == 'H')
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
        if (tipo == 'H')
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
        if (tipo == 'H')
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

bool verificarEspaco(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int x, int y, int tamanho, char tipo, char direcao, char sentido)
{
    bool espacoDisponivel = false;

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
        }
    }

    return espacoDisponivel;
}

void posicionarEmbarcacao(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], Embarcacao* embarcacao, int quantidade, int jogador)
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
                 << (embarcacao->tipo == 'S' ? "submarino" : embarcacao->tipo == 'C' ? "cruzador" : embarcacao->tipo == 'P' ? "porta-aviões" : embarcacao->tipo == 'E' ? "encouraçado" : "hidroavião")
                 << " " << i + 1 << " (ex: 1A): ";
            cin >> coordenada;

            int x = -1;
            int y = -1;
            if (coordenada.length() < 2)
            {
                cout << "\nCoordenada inválida! Tente novamente.\n";
                cout << "Pressione Enter para continuar...";
                cin.ignore();
                cin.get();
                continue;
            }

            int pos = 0;
            while (pos < coordenada.length() && isdigit(coordenada[pos]))
            {
                pos++;
            }

            if (pos == 0 || pos == coordenada.length())
            {
                cout << "\nFormato de coordenada inválido! Tente novamente.\n";
                cout << "Pressione Enter para continuar...";
                cin.ignore();
                cin.get();
                continue;
            }

            if (isdigit(coordenada[pos - 1]))
            {
                x = stoi(coordenada.substr(0, pos)) - 1;
                y = toupper(coordenada[pos]) - 'A';
            }
            else if (isdigit(coordenada[pos]))
            {
                y = toupper(coordenada[0]) - 'A';
                x = stoi(coordenada.substr(1, pos - 1)) - 1;
            }

            if (x < 0 || x >= TAMANHO_TABULEIRO || y < 0 || y >= TAMANHO_TABULEIRO)
            {
                cout << "\nCoordenada fora dos limites do tabuleiro! Tente novamente.\n";
                cout << "Pressione Enter para continuar...";
                cin.ignore();
                cin.get();
                continue;
            }

            if (embarcacao->tipo == 'S')   // Submarino
            {
                if (tabuleiro[y][x] == ' ')
                {
                    tabuleiro[y][x] = 'S';
                    posicaoValida = true;
                }
                else
                {
                    cout << "\nEspaço inválido para o submarino! Tente novamente.\n";
                    cout << "Pressione Enter para continuar...";
                    cin.ignore();
                    cin.get();
                }
            }
            else
            {
                char direcao;
                char sentido;
                if (!determinarDirecao(direcao, sentido, embarcacao->tipo))
                {
                    cout << "\nDireção ou sentido inválidos! Tente novamente.\n";
                    cout << "Pressione Enter para continuar...";
                    cin.ignore();
                    cin.get();
                    continue;
                }

                // Verificação para embarcações maiores, incluindo o hidroavião
                if (embarcacao->tipo == 'H')
                {
                    bool espacoDisponivel = false;

                    if (direcao == 'V' && sentido == 'D' && y + 1 < TAMANHO_TABULEIRO && y - 1 >= 0 && x + 1 < TAMANHO_TABULEIRO)
                    {
                        espacoDisponivel = (tabuleiro[y][x] == ' ' && tabuleiro[y + 1][x + 1] == ' ' && tabuleiro[y - 1][x + 1] == ' ');
                    }
                    else if (direcao == 'V' && sentido == 'E' && y + 1 < TAMANHO_TABULEIRO && y - 1 >= 0 && x - 1 >= 0)
                    {
                        espacoDisponivel = (tabuleiro[y][x] == ' ' && tabuleiro[y + 1][x - 1] == ' ' && tabuleiro[y - 1][x - 1] == ' ');
                    }
                    else if (direcao == 'H' && sentido == 'B' && y + 1 < TAMANHO_TABULEIRO && x + 1 < TAMANHO_TABULEIRO && x - 1 >= 0)
                    {
                        espacoDisponivel = (tabuleiro[y][x] == ' ' && tabuleiro[y + 1][x - 1] == ' ' && tabuleiro[y + 1][x + 1] == ' ');
                    }
                    else if (direcao == 'H' && sentido == 'C' && y + 1 < TAMANHO_TABULEIRO && x + 1 < TAMANHO_TABULEIRO && x - 1 >= 0)
                    {
                        espacoDisponivel = (tabuleiro[y][x] == ' ' && tabuleiro[y - 1][x - 1] == ' ' && tabuleiro[y - 1][x + 1] == ' ');
                    }

                    if (espacoDisponivel)
                    {
                        // Coloca a peça do hidroavião conforme a direção e o sentido
                        if (direcao == 'V' && sentido == 'D')
                        {
                            tabuleiro[y][x] = 'H';           // Peça central
                            tabuleiro[y + 1][x + 1] = 'H';   // Peça inferior direita
                            tabuleiro[y - 1][x + 1] = 'H';   // Peça superior direita
                        }
                        else if (direcao == 'V' && sentido == 'E')
                        {
                            tabuleiro[y][x] = 'H';           // Peça central
                            tabuleiro[y + 1][x - 1] = 'H';   // Peça inferior esquerda
                            tabuleiro[y - 1][x - 1] = 'H';   // Peça superior esquerda
                        }
                        else if (direcao == 'H' && sentido == 'C')
                        {
                            tabuleiro[y][x] = 'H';           // Peça central
                            tabuleiro[y - 1][x - 1] = 'H';   // Peça inferior esquerda
                            tabuleiro[y - 1][x + 1] = 'H';   // Peça inferior direita
                        }
                        else if (direcao == 'H' && sentido == 'B')
                        {
                            tabuleiro[y][x] = 'H';           // Peça central
                            tabuleiro[y + 1][x - 1] = 'H';   // Peça superior esquerda
                            tabuleiro[y + 1][x + 1] = 'H';   // Peça superior direita
                        }

                        posicaoValida = true;
                    }
                    else
                    {
                        cout << "\nEspaço inválido para o hidroavião! Tente novamente.\n";
                        cout << "Pressione Enter para continuar...";
                        cin.ignore();
                        cin.get();
                    }
                }
                else
                {
                    if (verificarEspaco(tabuleiro, x, y, embarcacao->tamanho, embarcacao->tipo, direcao, sentido))
                    {
                        posicaoValida = true;

                        if (direcao == 'V')
                        {
                            if (sentido == 'B')
                            {
                                for (int j = 0; j < embarcacao->tamanho; j++)
                                {
                                    tabuleiro[y + j][x] = embarcacao->tipo;
                                }
                            }
                            else if (sentido == 'C')
                            {
                                for (int j = 0; j < embarcacao->tamanho; j++)
                                {
                                    tabuleiro[y - j][x] = embarcacao->tipo;
                                }
                            }
                        }
                        else if (direcao == 'H')
                        {
                            if (sentido == 'D')
                            {
                                for (int j = 0; j < embarcacao->tamanho; j++)
                                {
                                    tabuleiro[y][x + j] = embarcacao->tipo;
                                }
                            }
                            else if (sentido == 'E')
                            {
                                for (int j = 0; j < embarcacao->tamanho; j++)
                                {
                                    tabuleiro[y][x - j] = embarcacao->tipo;
                                }
                            }
                        }
                    }
                    else
                    {
                        cout << "\nEspaço inválido para a embarcação! Tente novamente.\n";
                        cout << "Pressione Enter para continuar...";
                        cin.ignore();
                        cin.get();
                    }
                }
            }
        }
    }
}

void posicionarEmbarcacaoAutomaticamente(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], Embarcacao* embarcacao, int quantidade)
{
    for (int i = 0; i < quantidade; i++)
    {
        bool posicaoValida = false;
        while (!posicaoValida)
        {
            int x = rand() % TAMANHO_TABULEIRO;
            int y = rand() % TAMANHO_TABULEIRO;

            if (embarcacao->tipo == 'S')   // Submarino
            {
                if (tabuleiro[y][x] == ' ')
                {
                    tabuleiro[y][x] = 'S';
                    posicaoValida = true;
                }
            }
            else if (embarcacao->tipo == 'H')   // Hidroavião
            {
                char direcao = (rand() % 2 == 0) ? 'V' : 'H';
                char sentido = (rand() % 2 == 0) ? 'B' : 'C';

                if (direcao == 'V' && sentido == 'D' && y + 1 < TAMANHO_TABULEIRO && y - 1 >= 0 && x + 1 < TAMANHO_TABULEIRO)
                {
                    bool espacoDisponivel = (tabuleiro[y][x] == ' ' && tabuleiro[y + 1][x + 1] == ' ' && tabuleiro[y - 1][x + 1] == ' ');
                    if (espacoDisponivel)
                    {
                        tabuleiro[y][x] = 'H';           // Peça central
                        tabuleiro[y + 1][x + 1] = 'H';   // Peça inferior direita
                        tabuleiro[y - 1][x + 1] = 'H';   // Peça superior direita
                        posicaoValida = true;
                    }
                }
                else if (direcao == 'V' && sentido == 'E' && y + 1 < TAMANHO_TABULEIRO && y - 1 >= 0 && x - 1 >= 0)
                {
                    bool espacoDisponivel = (tabuleiro[y][x] == ' ' && tabuleiro[y + 1][x - 1] == ' ' && tabuleiro[y - 1][x - 1] == ' ');
                    if (espacoDisponivel)
                    {
                        tabuleiro[y][x] = 'H';           // Peça central
                        tabuleiro[y + 1][x - 1] = 'H';   // Peça inferior esquerda
                        tabuleiro[y - 1][x - 1] = 'H';   // Peça superior esquerda
                        posicaoValida = true;
                    }
                }
                else if (direcao == 'H' && sentido == 'B' && y + 1 < TAMANHO_TABULEIRO && x + 1 < TAMANHO_TABULEIRO && x - 1 >= 0)
                {
                    bool espacoDisponivel = (tabuleiro[y][x] == ' ' && tabuleiro[y + 1][x - 1] == ' ' && tabuleiro[y + 1][x + 1] == ' ');
                    if (espacoDisponivel)
                    {
                        tabuleiro[y][x] = 'H';           // Peça central
                        tabuleiro[y + 1][x - 1] = 'H';   // Peça superior esquerda
                        tabuleiro[y + 1][x + 1] = 'H';   // Peça superior direita
                        posicaoValida = true;
                    }
                }
                else if (direcao == 'H' && sentido == 'C' && y - 1 >= 0 && x + 1 < TAMANHO_TABULEIRO && x - 1 >= 0)
                {
                    bool espacoDisponivel = (tabuleiro[y][x] == ' ' && tabuleiro[y - 1][x - 1] == ' ' && tabuleiro[y - 1][x + 1] == ' ');
                    if (espacoDisponivel)
                    {
                        tabuleiro[y][x] = 'H';           // Peça central
                        tabuleiro[y - 1][x - 1] = 'H';   // Peça inferior esquerda
                        tabuleiro[y - 1][x + 1] = 'H';   // Peça inferior direita
                        posicaoValida = true;
                    }
                }
            }
            else
            {
                char direcao = (rand() % 2 == 0) ? 'V' : 'H';
                char sentido = (rand() % 2 == 0) ? 'B' : 'C';

                if (direcao == 'V' && sentido == 'B' && y + embarcacao->tamanho <= TAMANHO_TABULEIRO)
                {
                    bool espacoDisponivel = true;
                    for (int j = 0; j < embarcacao->tamanho; j++)
                    {
                        if (tabuleiro[y + j][x] != ' ')
                        {
                            espacoDisponivel = false;
                            break;
                        }
                    }

                    if (espacoDisponivel)
                    {
                        for (int j = 0; j < embarcacao->tamanho; j++)
                        {
                            tabuleiro[y + j][x] = embarcacao->tipo;
                        }
                        posicaoValida = true;
                    }
                }
                else if (direcao == 'V' && sentido == 'C' && y - embarcacao->tamanho + 1 >= 0)
                {
                    bool espacoDisponivel = true;
                    for (int j = 0; j < embarcacao->tamanho; j++)
                    {
                        if (tabuleiro[y - j][x] != ' ')
                        {
                            espacoDisponivel = false;
                            break;
                        }
                    }

                    if (espacoDisponivel)
                    {
                        for (int j = 0; j < embarcacao->tamanho; j++)
                        {
                            tabuleiro[y - j][x] = embarcacao->tipo;
                        }
                        posicaoValida = true;
                    }
                }
                else if (direcao == 'H' && sentido == 'D' && x + embarcacao->tamanho <= TAMANHO_TABULEIRO)
                {
                    bool espacoDisponivel = true;
                    for (int j = 0; j < embarcacao->tamanho; j++)
                    {
                        if (tabuleiro[y][x + j] != ' ')
                        {
                            espacoDisponivel = false;
                            break;
                        }
                    }

                    if (espacoDisponivel)
                    {
                        for (int j = 0; j < embarcacao->tamanho; j++)
                        {
                            tabuleiro[y][x + j] = embarcacao->tipo;
                        }
                        posicaoValida = true;
                    }
                }
                else if (direcao == 'H' && sentido == 'E' && x - embarcacao->tamanho + 1 >= 0)
                {
                    bool espacoDisponivel = true;
                    for (int j = 0; j < embarcacao->tamanho; j++)
                    {
                        if (tabuleiro[y][x - j] != ' ')
                        {
                            espacoDisponivel = false;
                            break;
                        }
                    }

                    if (espacoDisponivel)
                    {
                        for (int j = 0; j < embarcacao->tamanho; j++)
                        {
                            tabuleiro[y][x - j] = embarcacao->tipo;
                        }
                        posicaoValida = true;
                    }
                }
            }
        }
    }
}

void criarTabelaDeAtaque(char tabelaDeAtaque[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO])
{
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
        {
            tabelaDeAtaque[i][j] = VAZIO;
        }
    }
}

void mostrarTabelaDeAtaque(char tabelaDeAtaque[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], string player)
{
    cout << "Tabela de ataque do " << player << ":\n";
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
            switch (tabelaDeAtaque[j][i])
            {
            case 'F':
                cout << "FO ";
                break;
            case 'A':
                cout << "AG ";
                break;
            case ' ':
                cout << "[] ";
                break;
            default:
                cout << tabelaDeAtaque[j][i] << " ";
            }
        }
        cout << endl;
    }
}

void realizarAtaque(char tabelaDeAtaque[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int x, int y, int& pontos)
{
    // Se a célula já foi atacada anteriormente, não faz nada
    if (tabelaDeAtaque[y][x] == 'F' || tabelaDeAtaque[y][x] == 'A')
    {
        return;  // Não ganha pontos e não atualiza nada
    }
    if (tabuleiro[y][x] != VAZIO)
    {
        tabelaDeAtaque[y][x] = 'F';   // Acertou uma embarcação
        pontos++;  // Ganha um ponto ao acertar parte de uma embarcação
    }
    else
    {
        tabelaDeAtaque[y][x] = 'A';   // Não acertou nada (água)
    }
}

// Função para gerar coordenadas de ataque válidas (não repetidas)
void gerarAtaqueValido(char tabelaDeAtaque[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int& x, int& y)
{
    do
    {
        x = rand() % TAMANHO_TABULEIRO;
        y = rand() % TAMANHO_TABULEIRO;
    }
    while (tabelaDeAtaque[y][x] == 'F' || tabelaDeAtaque[y][x] == 'A');    // Gera novas coordenadas até encontrar uma célula não atacada
}

void menuBatalhaNaval()
{
    system("cls");
    setlocale(LC_ALL, "Portuguese");
    char tabuleiro1[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    char tabuleiro2[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    Embarcacao* hidroaviao = new Hidroaviao();
    Embarcacao* encouracado = new Encouracado();
    Embarcacao* portaavioes = new PortaAvioes();
    Embarcacao* submarino = new Submarino();
    Embarcacao* cruzador = new Cruzador();

    // Inicializa os tabuleiros com espaços vazios
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
        {
            tabuleiro1[i][j] = VAZIO;
            tabuleiro2[i][j] = VAZIO;
        }
    }
    int opcao;
    cout << "Batalha Naval\n";
    cout << "1. Jogador vs Jogador\n";
    cout << "2. Jogador vs Computador\n";
    cout << "3. Computador vs Computador\n";
    cout << "4. Sair\n";
    cout << "Escolha uma opção: ";
    cin >> opcao;

    switch (opcao)
    {
    case 1:
        system("cls");
        cout << "Jogador 1, posicione suas embarcações:\n";
        posicionarEmbarcacao(tabuleiro1, hidroaviao, 5, 1);
        posicionarEmbarcacao(tabuleiro1, encouracado, 2, 1);
        posicionarEmbarcacao(tabuleiro1, portaavioes, 1, 1);
        posicionarEmbarcacao(tabuleiro1, submarino, 4, 1);
        posicionarEmbarcacao(tabuleiro1, cruzador, 3, 1);

        cout << "Jogador 2, posicione suas embarcações:\n";
        posicionarEmbarcacao(tabuleiro2, hidroaviao, 5, 2);
        posicionarEmbarcacao(tabuleiro2, encouracado, 2, 2);
        posicionarEmbarcacao(tabuleiro2, portaavioes, 1, 2);
        posicionarEmbarcacao(tabuleiro2, submarino, 4, 2);
        posicionarEmbarcacao(tabuleiro2, cruzador, 3, 2);

        system("cls");
        mostrarTabela(tabuleiro1, "Jogador 1");
        cout << "\n\n";
        mostrarTabela(tabuleiro2, "Jogador 2");
        break;

    case 2:
        cout << "Modo Jogador vs Computador escolhido.\n";
        break;

    case 3:
    {
        system("cls");
        srand(time(0)); // Inicializa o gerador de números aleatórios

        // Computador 1
        cout << "Computador 1 está posicionando suas embarcações...\n";
        posicionarEmbarcacaoAutomaticamente(tabuleiro1, hidroaviao, 5);
        posicionarEmbarcacaoAutomaticamente(tabuleiro1, encouracado, 2);
        posicionarEmbarcacaoAutomaticamente(tabuleiro1, portaavioes, 1);
        posicionarEmbarcacaoAutomaticamente(tabuleiro1, submarino, 4);
        posicionarEmbarcacaoAutomaticamente(tabuleiro1, cruzador, 3);

        // Computador 2
        cout << "Computador 2 está posicionando suas embarcações...\n";
        posicionarEmbarcacaoAutomaticamente(tabuleiro2, hidroaviao, 5);
        posicionarEmbarcacaoAutomaticamente(tabuleiro2, encouracado, 2);
        posicionarEmbarcacaoAutomaticamente(tabuleiro2, portaavioes, 1);
        posicionarEmbarcacaoAutomaticamente(tabuleiro2, submarino, 4);
        posicionarEmbarcacaoAutomaticamente(tabuleiro2, cruzador, 3);

        char tabelaDeAtaque1[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
        char tabelaDeAtaque2[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

        criarTabelaDeAtaque(tabelaDeAtaque1);
        criarTabelaDeAtaque(tabelaDeAtaque2);

        system("cls");
        mostrarTabela(tabuleiro1, "Computador 1");
        cout << "\n\n";
        mostrarTabela(tabuleiro2, "Computador 2");

        cout << "\nPressione Enter para começar o ataque...";
        cin.get();
        cin.get();

        int rodada = 1;
        int pontosComputador1 = 0;
        int pontosComputador2 = 0;

        while (true)
        {
            system("cls");
            cout << "Rodada " << rodada << endl;

            int x, y;
            gerarAtaqueValido(tabelaDeAtaque1, x, y);
            realizarAtaque(tabelaDeAtaque1, tabuleiro2, x, y, pontosComputador1);

            cout << "Computador 1 atacou a posição (" << x + 1 << ", " << char(y + 'A') << ") do Computador 2\n";
            cout << "pontos compiuter 1: " << pontosComputador1 << endl;
            mostrarTabelaDeAtaque(tabelaDeAtaque1, "Computador 1");

            if (pontosComputador1 >= 38)
            {
                system("cls");
                cout << "Computador 1 venceu!\n"<< endl;
                cout << "pontos: " << pontosComputador1<< endl;
                cout << "pontos do compiuter 2: " <<  pontosComputador2 << endl;
                mostrarTabelaDeAtaque(tabelaDeAtaque1, "Computador 1");
                cout << "Pressione Enter para continuar...";
                cin.get();
                break;
            }

            system("cls");
            cout << "Rodada " << rodada << endl;

            // Computador 2 ataca Computador 1
            gerarAtaqueValido(tabelaDeAtaque2, x, y);
            realizarAtaque(tabelaDeAtaque2, tabuleiro1, x, y, pontosComputador2);

            cout << "Computador 2 atacou a posição (" << x + 1 << ", " << char(y + 'A') << ") do Computador 1\n";
            cout << "pontos compiuter 2: " << pontosComputador2 << endl;
            mostrarTabelaDeAtaque(tabelaDeAtaque2, "Computador 2");

            if (pontosComputador2 >= 38)
            {
                system("cls");
                cout << "Computador 2 venceu  "  << endl ;
                cout << "pontos: " << pontosComputador2  << endl;
                cout << "pontos do compiuter 1: " <<  pontosComputador1 << endl;
                mostrarTabelaDeAtaque(tabelaDeAtaque2, "Computador 2");
                cout << "Pressione Enter para continuar...";
                cin.get();
                break;
            }

            rodada++;
        }
        break;
    }

    case 4:
        cout << "Saindo do menu de Batalha Naval...\n";
        break;

    default:
        cout << "Opção inválida!\n";
        break;
    }

    // Liberação de memória
    delete hidroaviao;
    delete encouracado;
    delete portaavioes;
    delete submarino;
    delete cruzador;
}

void menuMatrizesVetores()
{
    system("cls");
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    cout << "Matrizes/Vetores\n";
    cout << "1. Batalha Naval\n";
    cout << "2. P2\n";
    cout << "3. P3\n";
    cout << "4. P4\n";
    cout << "5. Sair\n";
    cout << "Escolha uma opção: ";
    cin >> opcao;

    switch (opcao)
    {
    case 1:
        menuBatalhaNaval();
        break;
    case 2:
        cout << "P2 escolhido.\n";
        break;
    case 3:
        cout << "P3 escolhido.\n";
        break;
    case 4:
        cout << "P4 escolhido.\n";
        break;
    case 5:
        cout << "Saindo...\n";
        break;
    default:
        cout << "Opção inválida!\n";
        break;
    }
}

int main()
{
    system("cls");
    setlocale(LC_ALL, "Portuguese");
    int opcao;

    do
    {
        cout << "Menu Principal\n";
        cout << "1. P1 - Matrizes/Vetores\n";
        cout << "2. P2\n";
        cout << "3. P3\n";
        cout << "4. P4\n";
        cout << "5. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            menuMatrizesVetores();
            break;
        case 2:
            cout << "P2 escolhido.\n";
            break;
        case 3:
            cout << "P3 escolhido.\n";
            break;
        case 4:
            cout << "P4 escolhido.\n";
            break;
        case 5:
            cout << "Saindo do programa...\n";
            break;
        default:
            cout << "Opção inválida!\n";
            break;
        }
        cout << endl;
    }
    while (opcao != 5);

    return 0;
}
