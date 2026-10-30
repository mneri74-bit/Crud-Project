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
#include "windows.h"


#include  <fstream>
using namespace std;
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
    while (arquivo >> tipo) {
        arquivo.ignore();
        if (tipo == '$') {
            string nome, CPF;
            bool genero;
            int idade, salario, dia, mes, ano;
            float altura, peso, rating;
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
                string nome, CPF;
                bool genero;
                int idade, diatreino, skip, pagamento, dia, mes, ano;
                float altura, peso, c0, c1, c2;
                getline(arquivo, nome);
                arquivo >> idade >> genero;
                arquivo.ignore();     
                getline(arquivo, CPF);
                arquivo >> altura >> peso;
                arquivo >> diatreino >> skip >> pagamento;
                arquivo >> dia >> mes >> ano;
                arquivo >> c0 >> c1 >> c2;
                arquivo.ignore();

                povo.push_back(new cliente(nome, genero, idade, altura, peso, CPF, dia, mes, ano, pagamento,));
            }
        }
    }
        void listar(){
            int input;
            system("cls");
            for(int i=0; i<povo.size(); i++){
                cout<< i+1<< " - ";
                if(povo[i]->type()=='$'){cout<< "F";}
                else{cout<< "Cl";}
                cout<< povo[i]->nom()<< endl;
            }
        }
        void info(int input){
            system("cls");
            cin>> input;
            if(input<povo.size()){povo[input]->print();}
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
            cout << "Escolha o numero (0 para cancelar): ";
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

            cout << "\nCadastro atual:" << endl;
            povo[idx]->print();
            cout << "\nDigite os NOVOS dados:" << endl;

            string nome, CPF;
            bool genero;
            int idade, dia, mes, ano;
            float altura, peso;

            cout << "Nome: ";                      getline(cin >> ws, nome);
            cout << "Idade: ";                     cin >> idade;
            cout << "Genero (0/1): ";              cin >> genero;
            cout << "CPF: ";                       getline(cin >> ws, CPF);
            cout << "Altura: ";                    cin >> altura;
            cout << "Peso: ";                      cin >> peso;
            cout << "Data (dia mes ano): ";        cin >> dia >> mes >> ano;

            pessoa* novo = nullptr;
            if(povo[idx]->type() == '$'){
                int salario;
                float rating;
                cout << "Salario: ";               cin >> salario;
                cout << "Rating: ";                cin >> rating;
                novo = new funcionario(nome, genero, idade, altura, peso, CPF, salario, rating, dia, mes, ano);
            }else{
                int diatreino, skip, pagamento;
                float c0, c1, c2;
                cout << "Dia de treino: ";         cin >> diatreino;
                cout << "Skip: ";                  cin >> skip;
                cout << "Pagamento: ";             cin >> pagamento;
                cout << "c0 c1 c2: ";              cin >> c0 >> c1 >> c2;
                novo = new cliente(nome, genero, idade, altura, peso, CPF, dia, mes, ano, pagamento, c0, c1, c2, diatreino, skip);
            }

            // Se alguma leitura falhou (ex.: letra no lugar de número), não altera nada.
            if(!cin){
                cin.clear();
                cin.ignore(10000, '\n');
                delete novo;
                cout << "Entrada invalida. Nenhuma alteracao foi feita." << endl;
                return;
            }

            delete povo[idx];
            povo[idx] = novo;
            cout << "Cadastro alterado com sucesso!" << endl;
        }

        ~crud(){
             ofstream arquivo("registro.txt",ios::out);
            for(int i=0; i<povo.size(); i++){
                povo[i]->arquivo();
                }
            
        }
};
#endif
