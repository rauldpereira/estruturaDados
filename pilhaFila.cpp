#include <iostream>

using namespace std;

class PilhaVetor {
private:
    int pilha[10];
    int topo;

public:
    PilhaVetor() {
        topo = -1;
    }

    void empilhar(int valor) {
        if (topo < 9) {
            pilha[++topo] = valor;
        } else {
            cout << "Pilha cheia!" << endl;
        }
    }

    void desempilhar() {
        if (topo >= 0) {
            topo--;
        } else {
            cout << "Pilha vazia!" << endl;
        }
    }

    void imprimir() {
        for (int i = 0; i <= topo; i++) {
            cout << pilha[i] << " ";
        }
        cout << endl;
        cout << "Pressione Enter para continuar...";
        cin.get();
        cin.get();
    }
};

int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    cout << "Escolha uma opção:" << endl;
    cout << "1 - Pilha" << endl;
    cout << "2 - Fila" << endl;
    cout << "3 - Sair" << endl;
    cin >> opcao;

    switch (opcao) {
        case 1: {
            PilhaVetor pilha;
            int valor;
            while (true) {
                system("cls");

                cout << "Escolha uma opção:" << endl;
                cout << "1. Empilhar" << endl;
                cout << "2. Desempilhar" << endl;
                cout << "3. Imprimir" << endl;
                cout << "4. Sair" << endl;
                cin >> opcao;

                switch (opcao) {
                    case 1:
                        cout << "Digite um valor: ";
                        cin >> valor;
                        pilha.empilhar(valor);
                        break;
                    case 2:
                        pilha.desempilhar();
                        break;
                    case 3:
                        pilha.imprimir();
                        break;
                    case 4:
                        cout << "Saindo..." << endl;
                        return 0;
                    default:
                        cout << "Opção inválida!" << endl;
                }
            }
        }
        case 2:
        {
            cout << "fila" << endl;
            break;
        }
        case 3:
            {
                cout << "Saindo..." << endl;
                break;
            }
        default:
            cout << "Opção inválida!" << endl;
    }

    return 0;
}
