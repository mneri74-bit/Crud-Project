#ifndef crud_h
#define crud_h
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include "pessoa.hpp"
#include "cliente.hpp"
#include "funcionário.hpp"
#include <conio.h>
#include <iostream>
#include <windows.h>
using namespace std;
#include  <fstream>
using namespace std;
int gotoxy(int x, int y) {
    if(x >= 0 && y >= 0){
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        return 0;
    }
    return 1;
}
/*1. Inserir: cadastrar um novo registro.
2. Listar todos: exibir todos os registros cadastrados.
3. Exibir um: pesquisar e exibir um registro.
4. Alterar: pesquisar e modificar um registro. bom dia
5. Remover: pesquisar e excluir um registro.
6. Exibir relatório: apresentar um resumo dos dados.
7. Sair: encerrar o programa*/
class crud{
    private:
        // Converte para minúsculas (busca sem diferenciar maiúsculas/minúsculas)
        static string minusculo(string s){
            transform(s.begin(), s.end(), s.begin(),
                      [](unsigned char c){ return (char)tolower(c); });
            return s;
        }

    public:
        fstream arquivo;
        static vector<pessoa*> povo;

        crud(): arquivo("registro.txt", ios::in){
            if (!arquivo.is_open()) {
                cout << "Erro ao abrir o arquivo para leitura!" << endl;
                return;
                }
            char tipo;
            char barra;
                    string nome, CPF;
                    bool genero;
                    int idade;
                    float altura, peso;
            while (arquivo >> tipo) {
                arquivo.ignore();
                if (tipo == '$') {
                    int salario, dia, mes, ano;
                    float  rating;
                    getline(arquivo, nome);
                    arquivo >> idade;
                    arquivo >> genero;
                    arquivo.ignore();
                    getline(arquivo, CPF);
                    arquivo >> altura >> peso >> salario >> rating;
                    arquivo >> dia >> mes >> ano;
                    arquivo.ignore();
                    povo.push_back(new funcionario(nome, genero, idade, altura, peso, CPF, salario, rating, dia, mes, ano));
                }else if(tipo=='#'){
                        int pagamento, dia, mes, ano;
                        string matricula;
                        getline(arquivo, nome);
                        arquivo >> idade;
                        arquivo >> genero;
                        arquivo.ignore();
                        getline(arquivo, CPF);
                        arquivo >> altura >> peso;
                        arquivo >> pagamento;
                        arquivo >> dia >> barra >> mes >> barra >> ano;
                        arquivo.ignore();
                        getline(arquivo, matricula );
                        povo.push_back(new cliente(nome, genero, idade, altura, peso, CPF, dia, mes, ano, pagamento, matricula));
            }
        }
    }
        void info(int input){
            system("cls");
            cin>> input;
            if(input<povo.size() && input>0 ){povo[input]->print();}
        }

        void remover() {
        system("cls");
        if (povo.empty()) {
            cout << "nenhum registro\n";
            return;
        }
    }
        // Pesquisa por nome (ou parte do nome), sem diferenciar maiúsculas/minúsculas.
        // Retorna o índice da pessoa em povo, ou -1 se não encontrou / cancelou.
        int pesquisar(){
            string busca;
            cout << "Nome (ou parte do nome) a pesquisar: ";
            getline(cin >> ws, busca);
            string b = minusculo(busca);
            vector<int> achados;
            for(int i=0; i<(int)povo.size(); i++){
                string nome = povo[i]->nom();
                if(minusculo(nome).find(b) != string::npos){
                    achados.push_back(i);
                }
            }
            if(achados.empty()){
                cout << "Nenhum registro encontrado." << endl;
                return -1;
            }
            if(achados.size() == 1){
                return achados[0];
            }
            cout << "Foram encontrados varios registros:" << endl;
            cout << "Escolha o numero (0 para cancelar): \n";
            for(int k=0; k<(int)achados.size(); k++){
                int i = achados[k];
                cout << k+1 << " - ";
                cout << povo[i]->nom() ;
                cout << (povo[i]->type()=='$' ? "Funcionario" : "Cliente")<< endl;
            }
            int esc;
            cin >> esc;
            bool invalido = !cin || esc < 1 || esc > (int)achados.size();
            cin.clear();
            cin.ignore(10000, '\n');
            if(invalido) return -1;
            return achados[esc-1];
        }

        // Pesquisa uma pessoa e substitui o cadastro dela pelos novos dados digitados.
        void alterar(){
    system("cls");
    int idx = pesquisar();
    if(idx < 0) return;

    bool sair = false;
    while(!sair){
        system("cls");
        cout << "Cadastro atual:" << endl;
        povo[idx]->print();
        cout << "\n\nO que deseja alterar?\n";
        cout << "1- Nome\n";
        cout << "2- Idade\n";
        cout << "3- Genero (1-M / 0-F)\n";
        cout << "4- CPF\n";
        cout << "5- Altura\n";
        cout << "6- Peso\n";
        cout << "7- Data\n";
        if(povo[idx]->tipo == '$'){
            cout << "8- Salario\n";
            cout << "9- Rating\n";
        } else {
            cout << "8- Pagamento\n";
            cout << "9- Matricula\n";
        }
        cout << "0- Salvar e sair\n";

        char opc = getch();

        switch(opc){
            case '1':
                cout << "\nNovo nome: ";
                cin.ignore();
                getline(cin, povo[idx]->nome);
                break;
            case '2':
                cout << "\nNova idade: ";
                cin >> povo[idx]->idade;
                break;
            case '3':
                cout << "\nNovo genero (1-M / 0-F): ";
                cin >> povo[idx]->genero;
                break;
            case '4':
                cout << "\nNovo CPF: ";
                cin.ignore();
                getline(cin, povo[idx]->CPF);
                break;
            case '5':
                cout << "\nNova altura: ";
                cin >> povo[idx]->altura;
                break;
            case '6':
                cout << "\nNovo peso: ";
                cin >> povo[idx]->peso;
                break;
            case '7': {
                int dia, mes, ano;
                char barra;
                cout << "\nNova data (dia/mes/ano): ";
                cin >> dia >> barra >> mes >> barra >> ano;
                if(povo[idx]->tipo == '$'){
                    funcionario* f = dynamic_cast<funcionario*>(povo[idx]);
                    f->datadecontratacao.dia = dia;
                    f->datadecontratacao.mes = mes;
                    f->datadecontratacao.ano = ano;
                } else {
                    cliente* c = dynamic_cast<cliente*>(povo[idx]);
                    c->contratoprazo.dia = dia;
                    c->contratoprazo.mes = mes;
                    c->contratoprazo.ano = ano;
                }
                break;
            }
            case '8':
                if(povo[idx]->tipo == '$'){
                    funcionario* f = dynamic_cast<funcionario*>(povo[idx]);
                    cout << "\nNovo salario: ";
                    cin >> f->salario;
                } else {
                    cliente* c = dynamic_cast<cliente*>(povo[idx]);
                    cout << "\nNovo pagamento: ";
                    cin >> c->pagamento;
                }
                break;
            case '9':
                if(povo[idx]->tipo == '$'){
                    funcionario* f = dynamic_cast<funcionario*>(povo[idx]);                    
                    cout << "\nNovo rating: ";
                    cin >> f->rating;
                } else {
                    cliente* c = dynamic_cast<cliente*>(povo[idx]);
                    cout << "\nNova matricula: ";
                    cin >> c->matricula;
                }
                break;
            case '0':
                sair = true;
                break;
            default:
                cout << "\nOpcao invalida.\n";
        }
                if(!cin){
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Entrada invalida, tente novamente.\n";
                }
            }
             cout << "\nCadastro alterado com sucesso!" << endl;
        }
        ~crud(){
             ofstream arquivo("registro.txt",ios::out);
            for(int i=0; i<povo.size(); i++){
                povo[i]->arquivo();
                }
            
        }
};
#endif
