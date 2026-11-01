#include <iostream>
#include <string>
#include "data.hpp"
#include "pessoa.hpp"
#include "funcionário.hpp"
#include "cliente.hpp"
#include "crud.hpp"
#include <conio.h>
#include <windows.h>
using namespace std;

int main() {
    crud academia;

    char input = 0;
    while (input != '7') {
        system("cls");
        
        textcolor(PADRAO);
        cout << "\n";
        cout << "  +-------------------------------------------------+\n";
        textcolor(CIANO_CLARO);
        cout << "  |           SISTEMA DE GESTAO - ACADEMIA          |\n";
        textcolor(PADRAO);
        cout << "  +-------------------------------------------------+\n";
        cout << "  |                                                 |\n";
        cout << "  |   ";
        textcolor(VERDE_CLARO);
        cout << "1"; textcolor(PADRAO); cout << " - Inserir novo cadastro                      |\n";
        cout << "  |   ";
        textcolor(VERDE_CLARO); cout << "2"; textcolor(PADRAO); cout << " - Listar todos os registros                 |\n";
        cout << "  |   ";
        textcolor(VERDE_CLARO); cout << "3"; textcolor(PADRAO); cout << " - Exibir um registro (pesquisar)            |\n";
        cout << "  |   ";
        textcolor(VERDE_CLARO); cout << "4"; textcolor(PADRAO); cout << " - Alterar um registro                       |\n";
        cout << "  |   ";
        textcolor(VERDE_CLARO); cout << "5"; textcolor(PADRAO); cout << " - Remover um registro                       |\n";
        cout << "  |   ";
        textcolor(VERDE_CLARO); cout << "6"; textcolor(PADRAO); cout << " - Exibir relatorio geral                    |\n";
        cout << "  |   ";
        textcolor(VERMELHO_CLARO); cout << "7"; textcolor(PADRAO); cout << " - Sair do sistema                           |\n";
        cout << "  |                                                 |\n";
        cout << "  +-------------------------------------------------+\n";
        
        textcolor(AMARELO_CLARO);
        cout << "\n  Escolha uma opcao: ";
        textcolor(PADRAO);
        
        input = getch();
        
        switch (input) {
            case '1': academia.add(); break;
            case '2': academia.listar(); break;
            case '3': academia.exibir(); break;
            case '4': academia.alterar(); break;
            case '5': academia.remover(); break;
            case '6': academia.relatorio(); break;
            case '7': break;
            default:
                textcolor(VERMELHO_CLARO);
                cout << "\n  Opcao invalida!";
                textcolor(PADRAO);
                Sleep(1000);
                break;
        }
        
        if(input >= '1' && input <= '6') {
            textcolor(CINZA_ESCURO);
            cout << "\n\n  Pressione ENTER para voltar ao menu...";
            textcolor(PADRAO);
            cin.get();
        }
    }
    
    system("cls");
    textcolor(VERDE_CLARO);
    cout << "\n\n  Saindo do sistema... Volte sempre :)\n\n";
    textcolor(PADRAO);
    Sleep(1500);
    return 0;
}