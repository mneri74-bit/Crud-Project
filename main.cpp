#include <iostream>
#include "data.hpp"
#include "pessoa.hpp"
#include "funcionário.hpp"
#include "cliente.hpp"
#include "crud.hpp"
#include <conio.h>
#include <windows.h>
using namespace std;
/*1. Inserir
2. Listar todos
3. Exibir um
4. Alterar
5. Remover
6. Exibir relatório
7. Sair*/
int main() {
    crud academia;
    char input = 0;
    while (input != '7') {
        system("cls");
        cout << "=== Academia - CRUD ===\n";
        cout << "1 - Inserir\n";
        cout << "2 - Listar todos\n";
        cout << "3 - Exibir um\n";
        cout << "4 - Alterar\n";
        cout << "5 - Remover\n";
        cout << "6 - Relatorio\n";
        cout << "7 - Sair\n";
        cout << "Escolha uma opcao: ";
        input = getch();
        cout << input << "\n";
        switch (input){
            case '1':
                academia.add();
                getch();
                break;
            case '2':
                academia.listar();
                getch();
                break;
            case '3':
                academia.exibir();
                getch();
                break;
            case '4':
                academia.alterar();
                getch();
                break;
            case '5':
                academia.remover();
                getch();
                break;
            case '6':
                academia.relatorio();
                getch();
                break;
            case '7':
                break;
            default:
                cout << "Opcao invalida.\n";
                getch();
                break;
        }
    }
    system("cls");
    cout << "Volte sempre :)\n";
}