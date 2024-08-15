#include <iostream>

using namespace std;

void showTable()
{
    system("cls");

    char letra[16] = "ABCDEFGHIJKLMNO";
    cout << "  ";
    for (int i = 0; i < 15; i++)
    {
        if (i < 9)
            cout << "0"<< i + 1 << " ";
        else
            cout << i + 1 << ' ';

    }
    cout << endl;
    for (int j = 0; j < 15; j++)
    {
        cout << letra[j] << ' ';
        for(int i = 0; i < 15; i++){
            cout << "[ ]";
        }
        cout << endl;
    }

    cout << "Tecle <Enter> para fechar a tabela... ";
    cin.ignore();
    cin.get();
}



void batalhaNaval()
{
    cout << "Batalha Naval\n";
    int op = 0;

    int matriz_escolha_jogador[15][15];

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
            showTable();
            for(int i = 0; i <= 14; i++)
            {
                cout<<"\n";

                for(int j = 0; j <= 14; j++)
                {
                    cout << matriz_escolha_jogador[i][j];
                }
            }
            break;
        case 2:
            cout << "Player vs CPU\n";
            showTable();
            break;
        case 3:
            cout << "CPU vs CPU\n";
            showTable();
            break;
        case 4:
            cout << "Saindo...";
            break;
        default:
            cout << "Opção Invalida.\n";
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
                cout << "Opção Invalida.\n";
                break;
        }
    }
    return 0;
}
