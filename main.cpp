#include <iostream>
#include "data.hpp"
#include "pessoa.hpp"
#include "funcionário.hpp"
#include "cliente.hpp"
#include "crud.hpp"
#include <conio.h>
#include <windows.h>
using namespace std;
/*1. Inserir: cadastrar um novo registro.x
2. Listar todos: exibir todos os registros cadastrados. x
3. Exibir um: pesquisar e exibir um registro.x
4. Alterar: pesquisar e modificar um registro.x
5. Remover: pesquisar e excluir um registro.x
6. Exibir relatório: apresentar um resumo dos dados.
7. Sair: encerrar o programa*/
int main() {
    crud academia;
    system("cls");
    int input;
    while(input!=7){
        if(kbhit()){
            input = getch();
            switch (input){
            case 1:
                academia.add();
                break;
            case 2:
                academia.listar();
                break;
            case 3:
                //exibir um
                break;
            case 4:
                //alterar
                break;
            case 5:
                academia.remover();
                break;
            case 6:
                //relatório
                break;
            case 7:
                system("cls");
                cout<< "Volte sempre :)";
                break;
            default:
                cout<< "comando inválido";
                break;
            }
        }
    }
}

