#ifndef crud_h
#define crud_h
#include <string>
#include <iostream>
#include <vector>
#include "pessoa.hpp"
#include "cliente.hpp"
#include "funcionário.hpp"
#include "windows.h"


#include  <fstream>
using namespace std;
/*1. Inserir: cadastrar um novo registro.x
2. Listar todos: exibir todos os registros cadastrados. x
3. Exibir um: pesquisar e exibir um registro.x
4. Alterar: pesquisar e modificar um registro.x
5. Remover: pesquisar e excluir um registro.x
6. Exibir relatório: apresentar um resumo dos dados.
7. Sair: encerrar o programa*/
class crud{
    private:
    
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
                        getline(cin, nome);
                        cout << "digite a idade" << endl;
                        cin >> idade;
                        cout << "digite o genero" << endl;
                        cin >> genero;
                        cin.ignore();
                        cout << "digite o CPF" << endl;
                        getline(cin, CPF);
                        cout << "digite a altura e o peso" << endl;
                        cin >> altura >> peso;
                        cout << "digite o pagamento mensal" << endl;
                        cin >> pagamento;
                        cout << "digite a data do contrato no formato: dia/mes/ano" << endl;
                        cin >> dia >> barra >> mes >> barra >> ano;
                        cin.ignore();
                        getline(arquivo, matricula );
                        povo.push_back(new cliente(nome, genero, idade, altura, peso, CPF, dia, mes, ano, pagamento, matricula));
            }
        }
    }
        void listar(){
            int input;
            system("cls");
            for(int i=0; i<povo.size(); i++){
                cout<< i+1<< " - ";
                cout<< povo[i]->nom()<< endl;
                if(povo[i]->type()=='$'){cout<< "F";}
                else{cout<< "Cl";}
            }
        }
        
        void add(){
            bool tipo;
            cout<< "Qual tipo de cadastro você vai querer fazer?\n0-Cliente 1-Funcionário";
            cin>>  tipo;
            char barra;
            string nome, CPF;
            bool genero;
            int idade;
            float altura, peso;
            if (tipo){               
                int salario, dia, mes, ano;
                float rating;
                cout<< "Digite o nome"<< endl;
                getline(cin, nome);
                cout<< "digite a idade"<< endl;
                cin >> idade;
                cout<< "digite o genero"<< endl;
                cin >> genero;
                cin.ignore();
                cout<< "digite o CPF"<< endl;
                getline(cin, CPF);
                cout<< "digite a altura e o peso"<< endl;
                cin >> altura >> peso; 
                cout<< "digite o salario mensal e a avaliacao do funcionario"<< endl;
                cin >> salario >> rating;
                cout<< "digite a data da contratacao no formato: dia/mes/ano";
                cin >> dia >> barra >> mes >> barra >> ano;
                cin.ignore();
                povo.push_back(new funcionario(nome, genero, idade, altura, peso, CPF, salario, rating, dia, mes, ano)); 
            }else{
                int pagamento, dia, mes, ano;
                string matricula;
                cout << "Digite o nome" << endl;
                getline(cin, nome);
                cout << "digite a idade" << endl;
                cin >> idade;
                cout << "digite o genero" << endl;
                cin >> genero;
                cin.ignore();
                cout << "digite o CPF" << endl;
                getline(cin, CPF);
                cout << "digite a altura e o peso" << endl;
                cin >> altura >> peso;
                cout << "digite o pagamento mensal" << endl;
                cin >> pagamento;
                cout << "digite a data do contrato no formato: dia/mes/ano" << endl;
                cin >> dia >> barra >> mes >> barra >> ano;
                cin.ignore();
                getline(arquivo, matricula );
                povo.push_back(new cliente(nome, genero, idade, altura, peso, CPF, dia, mes, ano, pagamento, matricula));
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
        string nome;
        cout << "remover pelo nome: ";
        getline(cin >> ws, nome);   
        int i = pesquisar(nome);
        if (i < 0 || i >= (int)povo.size()) {
            cout << "falha ao encontrar registro.\n";
            return;
        }
        string removido = povo[i]->nom();    
        delete povo[i];                      
        povo.erase(povo.begin() + i);        
        cout << removido << " removido(a).\n";
}

        ~crud(){
             ofstream arquivo("registro.txt",ios::out);
            for(int i=0; i<povo.size(); i++){
                povo[i]->arquivo();
                }
        }
};
#endif
