#include <iostream>

using namespace std;

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
                cout << "Matrizes/Vetores\n";
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
                cout << "Opção Invalida.";
                break;
        }
    }
    return 0;
}
