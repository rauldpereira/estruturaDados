#include <iostream>

using namespace std;

class PilhaVetor
{
private:
    int pilha[10];
    int topo;

public:
    PilhaVetor()
    {
        topo = -1;
    }

    void empilhar(int valor)
    {
        if (topo < 9)
        {
            pilha[++topo] = valor;
        }
        else
        {
            cout << "Pilha cheia!" << endl;
        }
    }

    void desempilhar()
    {
        if (topo >= 0)
        {
            topo--;
        }
        else
        {
            cout << "Pilha vazia!" << endl;
        }
    }

    void imprimir()
    {
        for (int i = 0; i <= topo; i++)
        {
            cout << pilha[i] << " ";
        }
        cout << endl;
        cout << "Pressione Enter para continuar...";
        cin.get();
        cin.get();
    }
};

class FilaVetor
{
private:
    int fila[10];
    int inicio;
    int fim;
    int tamanho;

public:
    FilaVetor()
    {
        inicio = 0;
        fim = 0;
        tamanho = 0;
    }

    void enfileirar(int valor)
    {
        if (tamanho < 10)
        {
            fila[fim] = valor;
            fim = (fim + 1) % 10;
            tamanho++;
        }
        else
        {
            cout << "Fila cheia!" << endl;
        }
    }

    void desenfileirar()
    {
        if (tamanho > 0)
        {
            inicio = (inicio + 1) % 10;
            tamanho--;
        }
        else
        {
            cout << "Fila vazia!" << endl;
        }
    }

    void imprimir()
    {
        for (int i = 0; i < tamanho; i++)
        {
            cout << fila[(inicio + i) % 10] << " ";
        }
        cout << endl;
        cout << "Pressione Enter para continuar...";
        cin.get();
        cin.get();
    }
};

class No
{
public:
    int valor;
    No* proximo;

    No(int valor)
    {
        this->valor = valor;
        this->proximo = nullptr;
    }
};

class PilhaPonteiro
{
private:
    No* topo;

public:
    PilhaPonteiro()
    {
        topo = nullptr;
    }

    void empilhar(int valor)
    {
        No* novoNo = new No(valor);
        if (topo == nullptr)
        {
            topo = novoNo;
        }
        else
        {
            novoNo->proximo = topo;
            topo = novoNo;
        }
    }

    void desempilhar()
    {
        if (topo == nullptr)
        {
            cout << "Pilha vazia!" << endl;
        }
        else
        {
            No* temp = topo;
            topo = topo->proximo;
            delete temp;
        }
    }

    void imprimir()
    {
        No* temp = topo;
        while (temp != nullptr)
        {
            cout << temp->valor << " ";
            temp = temp->proximo;
        }
        cout << endl;
        cout << "Pressione Enter para continuar...";
        cin.get();
        cin.get();
    }

    ~PilhaPonteiro()
    {
        while (topo != nullptr)
        {
            No* temp = topo;
            topo = topo->proximo;
            delete temp;
        }
    }
};

class FilaPonteiro
{
private:
    No* inicio;
    No* fim;

public:
    FilaPonteiro()
    {
        inicio = nullptr;
        fim = nullptr;
    }

    void enfileirar(int valor)
    {
        No* novoNo = new No(valor);
        if (inicio == nullptr)
        {
            inicio = novoNo;
            fim = novoNo;
        }
        else
        {
            fim->proximo = novoNo;
            fim = novoNo;
        }
    }

    void desenfileirar()
    {
        if (inicio == nullptr)
        {
            cout << "Fila vazia!" << endl;
        }
        else
        {
            No* temp = inicio;
            inicio = inicio->proximo;
            if (inicio == nullptr)
            {
                fim = nullptr;
            }
            delete temp;
        }
    }

    void imprimir()
    {
        No* temp = inicio;
        while (temp != nullptr)
        {
            cout << temp->valor << " ";
            temp = temp->proximo;
        }
        cout << endl;
        cout << "Pressione Enter para continuar...";
        cin.get();
        cin.get();
    }

    ~FilaPonteiro()
    {
        while (inicio != nullptr)
        {
            No* temp = inicio;
            inicio = inicio->proximo;
            delete temp;
        }
    }
};

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    cout << "Escolha uma opcao:" << endl;
    cout << "1 - Pilha Vetor" << endl;
    cout << "2 - Fila Vetor" << endl;
    cout << "3 - Pilha Ponteiro" << endl;
    cout << "4 - Fila Ponteiro" << endl;
    cout << "5 - Sair" << endl;
    cin >> opcao;

    switch (opcao)
    {
    case 1:
    {
        PilhaVetor pilha;
        int valor;
        while (true)
        {
            system("cls");

            cout << "Escolha uma opcao:" << endl;
            cout << "1. Empilhar" << endl;
            cout << "2. Desempilhar" << endl;
            cout << "3. Imprimir" << endl;
            cout << "4. Sair" << endl;
            cin >> opcao;

            switch (opcao)
            {
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
                cout << "Opcao inválida!" << endl;
            }
        }
    }
    case 2:
    {
        FilaVetor fila;
        int valor;
        while (true)
        {
            system("cls");

            cout << "Escolha uma opcao:" << endl;
            cout << "1. Enfileirar" << endl;
            cout << "2. Desenfileirar" << endl;
            cout << "3. Imprimir" << endl;
            cout << "4. Sair" << endl;
            cin >> opcao;

            switch (opcao)
            {
            case 1:
                cout << "Digite um valor: ";
                cin >> valor;
                fila.enfileirar(valor);
                break;
            case 2:
                fila.desenfileirar();
                break;
            case 3:
                fila.imprimir();
                break;
            case 4:
                cout << "Saindo..." << endl;
                return 0;
            default:
                cout << "Opcao inválida!" << endl;
            }
        }
    }
    case 3:
    {
        PilhaPonteiro pilha;
        int valor;
        while (true)
        {
            system("cls");

            cout << "Escolha uma opcao:" << endl;
            cout << "1. Empilhar" << endl;
            cout << "2. Desempilhar" << endl;
            cout << "3. Imprimir" << endl;
            cout << "4. Sair" << endl;
            cin >> opcao;

            switch (opcao)
            {
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
                cout << "Opcao inválida!" << endl;
            }
        }
    }
    case 4:
    {
        FilaPonteiro fila;
        int valor;
        while (true)
        {
            system("cls");

            cout << "Escolha uma opcao:" << endl;
            cout << "1. Enfileirar" << endl;
            cout << "2. Desenfileirar" << endl;
            cout << "3. Imprimir" << endl;
            cout << "4. Sair" << endl;
            cin >> opcao;

            switch (opcao)
            {
            case 1:
                cout << "Digite um valor: ";
                cin >> valor;
                fila.enfileirar(valor);
                break;
            case 2:
                fila.desenfileirar();
                break;
            case 3:
                fila.imprimir();
                break;
            case 4:
                cout << "Saindo..." << endl;
                return 0;
            default:
                cout << "Opcao inválida!" << endl;
            }
        }
    }
    case 5:
        cout << "Saindo..." << endl;
        break;
    default:
        cout << "Opcao invalida!" << endl;
    }
    return 0;
}
