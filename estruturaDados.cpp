#include <iostream>

using namespace std;

void showTable()
{
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
}

void matrizesVetores()
{
    cout << "Matrizes/Vetores\n";
    int op = 0;

    while (op != 4)
    {
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

int main(void)
{
    int op = 0;

    while (op != 5)
    {
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
