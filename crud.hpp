#ifndef crud_h
#define crud_h
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include "pessoa.hpp"
#include "cliente.hpp"
#include "funcionário.hpp"
#include "data.hpp"
using namespace std;

inline int gotoxy(int x, int y) {
    if(x >= 0 && y >= 0){
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        return 0;
    }
    return 1;
}

class crud{
    private:
        static string minusculo(string s){
            transform(s.begin(), s.end(), s.begin(),
                      [](unsigned char c){ return (char)tolower(c); });
            return s;
        }

        Data dataAbertura;
        string nomeAcademia;
        string endereco;
        string cnpj;

    public:
        fstream arquivo;
        vector<pessoa*> povo;

        void recalcularBest(){
            funcionario::best = nullptr;
            for (int i = 0; i < (int)povo.size(); i++){
                if (povo[i]->tipo == '$'){
                    funcionario* f = dynamic_cast<funcionario*>(povo[i]);
                    if (!funcionario::best || funcionario::best->rating < f->rating)
                        funcionario::best = f;
                }
            }
        }

        bool cpfExiste(string cpf, int ignorar = -1){
            for (int i = 0; i < (int)povo.size(); i++){
                if (i == ignorar) continue;
                if (povo[i]->CPF == cpf) return true;
            }
            return false;
        }

        bool matriculaExiste(string mat, int ignorar = -1){
            for (int i = 0; i < (int)povo.size(); i++){
                if (i == ignorar) continue;
                if (povo[i]->tipo == '$') continue;
                cliente* c = dynamic_cast<cliente*>(povo[i]);
                if (c->matricula == mat) return true;
            }
            return false;
        }

        crud() : arquivo("registro.txt", ios::in) {
            system("cls");
            cout << "=== CONFIGURACAO INICIAL ===" << endl;
            cout << "Digite o nome da academia: ";
            getline(cin >> ws, nomeAcademia);
            cout << "Digite o endereco da academia: ";
            getline(cin >> ws, endereco);

            time_t t = time(0);
            tm* now = localtime(&t);
            dataAbertura = Data(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);

            srand(time(NULL));
            string tempCNPJ = "";
            for(int i = 0; i < 14; i++){
                tempCNPJ += to_string(rand() % 10);
            }
            cnpj = tempCNPJ.substr(0,2) + "." + tempCNPJ.substr(2,3) + "." + 
                   tempCNPJ.substr(5,3) + "/" + tempCNPJ.substr(8,4) + "-" + tempCNPJ.substr(12,2);

            if (!arquivo.is_open()) {
                cout << "\nNenhum registro ainda. Crie um novo cadastro." << endl;
            } else {
                char tipo;
                string nome, CPF;
                bool genero;
                int idade;
                float altura, peso;
                while (arquivo >> tipo) {
                    arquivo.ignore();
                    if (tipo == '$') {
                        int salario, dia, mes, ano;
                        float rating;
                        string cargo;
                        getline(arquivo, nome);
                        arquivo >> idade;
                        arquivo >> genero;
                        arquivo.ignore();
                        getline(arquivo, CPF);
                        arquivo >> altura >> peso;
                        getline(arquivo >> ws, cargo);
                        arquivo >> salario >> rating;
                        arquivo >> dia >> mes >> ano;
                        arquivo.ignore();
                        povo.push_back(new funcionario(nome, genero, idade, altura, peso, CPF,
                                                       cargo, salario, rating, dia, mes, ano));
                    } else if (tipo == '#') {
                        int pagamento, dia, mes, ano;
                        string matricula;
                        getline(arquivo, nome);
                        arquivo >> idade;
                        arquivo >> genero;
                        arquivo.ignore();
                        getline(arquivo, CPF);
                        arquivo >> altura >> peso;
                        arquivo >> pagamento;
                        arquivo >> dia >> mes >> ano;
                        arquivo.ignore();
                        getline(arquivo, matricula);
                        povo.push_back(new cliente(nome, genero, idade, altura, peso, CPF, dia, mes, ano, pagamento, matricula));
                    }
                }
            }
            recalcularBest();
        }

        void listar(){
            system("cls");
            for(int i=0; i<(int)povo.size(); i++){
                cout<< i+1<< " - ";
                cout<< povo[i]->nome;
                if(povo[i]->type()=='$'){cout<< " - Funcionario"<< endl;}
                else{cout<<  " - Cliente"<< endl;}
            }          
        }

        void exibir(){
            listar();
            cout << "Qual elemento voce quer exibir (0 para cancelar): ";
            int input;
            cin >> input;
            if (!cin) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Entrada invalida." << endl;
                return;
            }
            if (input == 0) return;
            input--; 
            info(input);
        }

        void add(){
            int tipo = -1;
            cout<< "Qual tipo de cadastro você vai querer fazer?\n0-Cliente\n1-Funcionário\n";
            cin>> tipo;
            if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Entrada invalida." << endl; return; }
            cin.ignore();
            if (tipo != 0 && tipo != 1){
                cout << "Opcao invalida." << endl;
                return;
            }
            char barra;
            string nome, CPF;
            bool genero;
            int idade = 0;
            float altura = 0, peso = 0;
            if (tipo == 1){
                int salario = 0, dia = 0, mes = 0, ano = 0, g = -1;
                float rating = 0;
                string cargo;
                cout<< "Digite o nome"<< endl;
                getline(cin, nome);
                cout<< "digite a idade"<< endl;
                cin >> idade;
                if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Entrada invalida." << endl; return; }
                cout<< "digite o genero (1-M / 0-F)"<< endl;
                cin >> g;
                if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Entrada invalida." << endl; return; }
                if (g != 0 && g != 1){ cout << "Genero invalido." << endl; return; }
                genero = (g == 1);
                cin.ignore();
                cout<< "digite o CPF"<< endl;
                getline(cin, CPF);
                /*do{
                } while (cpfExiste(CPF));*/
                
                if (cpfExiste(CPF)){ cout << "CPF ja cadastrado, digite outro CPF." << endl; return; }
                cout<< "digite a altura e o peso"<< endl;
                cin >> altura >> peso;
                if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Entrada invalida." << endl; return; }
                cout<< "digite o cargo"<< endl;
                getline(cin >> ws, cargo);
                cout<< "digite o salario mensal e a avaliacao do funcionario"<< endl;
                cin >> salario >> rating;
                if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Entrada invalida." << endl; return; }
                cout<< "digite a data da contratacao no formato: dia/mes/ano"<< endl;
                cin >> dia >> barra >> mes >> barra >> ano;
                if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Entrada invalida." << endl; return; }
                cin.ignore();
                povo.push_back(new funcionario(nome, genero, idade, altura, peso, CPF,
                                               cargo, salario, rating, dia, mes, ano));
            }else{
                int pagamento = 0, dia = 0, mes = 0, ano = 0, g = -1;
                string matricula;
                cout << "Digite o nome" << endl;
                getline(cin, nome);
                cout << "digite a idade" << endl;
                cin >> idade;
                if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Entrada invalida." << endl; return; }
                cout << "digite o genero (1-M / 0-F)" << endl;
                cin >> g;
                if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Entrada invalida." << endl; return; }
                if (g != 0 && g != 1){ cout << "Genero invalido." << endl; return; }
                genero = (g == 1);
                cin.ignore();
                cout << "digite o CPF" << endl;
                getline(cin, CPF);
                if (cpfExiste(CPF)){ cout << "CPF ja cadastrado." << endl; return; }
                cout << "digite a altura e o peso" << endl;
                cin >> altura >> peso;
                if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Entrada invalida." << endl; return; }
                cout << "digite o pagamento mensal" << endl;
                cin >> pagamento;
                if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Entrada invalida." << endl; return; }
                cout << "digite a data do contrato no formato: dia/mes/ano" << endl;
                cin >> dia >> barra >> mes >> barra >> ano;
                if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Entrada invalida." << endl; return; }
                cin.ignore();
                cout << "digite a matricula" << endl;
                getline(cin, matricula);
                if (matriculaExiste(matricula)){ cout << "Matricula ja cadastrada." << endl; return; }
                povo.push_back(new cliente(nome, genero, idade, altura, peso, CPF, dia, mes, ano, pagamento, matricula));
            }
            recalcularBest();
        }

        void info(int input){
            system("cls");
            if(input >= 0 && input < (int)povo.size() ){povo[input]->print();}
        }

        int Pesquisar(string nome){
            string b = minusculo(nome);
            if (b.empty()){
                cout << "Busca vazia." << endl;
                return -1;
            }
            vector<int> achados;
            for(int i=0; i<(int)povo.size(); i++){
                string nomeMin = minusculo(povo[i]->nom());
                if(nomeMin.find(b) == 0){
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
                cout << povo[i]->nom() << " - ";
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

        int pesquisar(){
            string busca;
            cout << "Nome (ou parte do nome) a pesquisar: ";
            getline(cin >> ws, busca);
            return Pesquisar(busca);
        }

        void alterar(){
            system("cls");
            int idx = pesquisar();
            if(idx < 0) return;

            bool sair = false;
            bool mudou = false;
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
                    cout << "a- Cargo\n";
                } else {
                    cout << "8- Pagamento\n";
                    cout << "9- Matricula\n";
                }
                cout << "0- Salvar e sair\n";

                char opc = getch();

                switch(opc){
                    case '1':
                        cout << "\nNovo nome: ";
                        getline(cin >> ws, povo[idx]->nome);
                        mudou = true;
                        break;
                    case '2': {
                        int novaIdade;
                        cout << "\nNova idade: ";
                        cin >> novaIdade;
                        if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Invalido." << endl; break; }
                        povo[idx]->idade = novaIdade;
                        mudou = true;
                        break;
                    }
                    case '3': {
                        int g;
                        cout << "\nNovo genero (1-M / 0-F): ";
                        cin >> g;
                        if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Invalido." << endl; break; }
                        if (g == 0 || g == 1) { povo[idx]->genero = (g == 1); mudou = true; }
                        else cout << "\nGenero invalido." << endl;
                        break;
                    }
                    case '4': {
                        cout << "\nNovo CPF: ";
                        string novoCPF;
                        getline(cin >> ws, novoCPF);
                        if (cpfExiste(novoCPF, idx)) cout << "\nCPF ja cadastrado." << endl;
                        else { povo[idx]->CPF = novoCPF; mudou = true; }
                        break;
                    }
                    case '5': {
                        float novaAltura;
                        cout << "\nNova altura: ";
                        cin >> novaAltura;
                        if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Invalido." << endl; break; }
                        povo[idx]->altura = novaAltura;
                        if(povo[idx]->tipo == '#') dynamic_cast<cliente*>(povo[idx])->calcularIMC();
                        mudou = true;
                        break;
                    }
                    case '6': {
                        float novoPeso;
                        cout << "\nNovo peso: ";
                        cin >> novoPeso;
                        if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Invalido." << endl; break; }
                        povo[idx]->peso = novoPeso;
                        if(povo[idx]->tipo == '#') dynamic_cast<cliente*>(povo[idx])->calcularIMC();
                        mudou = true;
                        break;
                    }
                    case '7': {
                        int dia = 0, mes = 0, ano = 0;
                        char barra;
                        cout << "\nNova data (dia/mes/ano): ";
                        cin >> dia >> barra >> mes >> barra >> ano;
                        if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Invalido." << endl; break; }
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
                        mudou = true;
                        break;
                    }
                    case '8': {
                        if(povo[idx]->tipo == '$'){
                            funcionario* f = dynamic_cast<funcionario*>(povo[idx]);
                            int novoSalario;
                            cout << "\nNovo salario: ";
                            cin >> novoSalario;
                            if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Invalido." << endl; break; }
                            f->salario = novoSalario;
                        } else {
                            cliente* c = dynamic_cast<cliente*>(povo[idx]);
                            int novoPag;
                            cout << "\nNovo pagamento: ";
                            cin >> novoPag;
                            if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Invalido." << endl; break; }
                            c->pagamento = novoPag;
                        }
                        mudou = true;
                        break;
                    }
                    case '9': {
                        if(povo[idx]->tipo == '$'){
                            funcionario* f = dynamic_cast<funcionario*>(povo[idx]);
                            float novoRating;
                            cout << "\nNovo rating: ";
                            cin >> novoRating;
                            if (!cin) { cin.clear(); cin.ignore(10000, '\n'); cout << "Invalido." << endl; break; }
                            f->rating = novoRating;
                            recalcularBest();
                            mudou = true;
                        } else {
                            cliente* c = dynamic_cast<cliente*>(povo[idx]);
                            cout << "\nNova matricula: ";
                            string novaMat;
                            getline(cin >> ws, novaMat);
                            if (matriculaExiste(novaMat, idx)) cout << "\nMatricula ja cadastrada." << endl;
                            else { c->matricula = novaMat; mudou = true; }
                        }
                        break;
                    }
                    case 'a': {
                        if(povo[idx]->tipo == '$'){
                            funcionario* f = dynamic_cast<funcionario*>(povo[idx]);
                            cout << "\nNovo cargo: ";
                            getline(cin >> ws, f->cargo);
                            mudou = true;
                        }
                        break;
                    }
                    case '0':
                        sair = true;
                        break;
                    default:
                        cout << "\nOpcao invalida.\n";
                }
            }
            if (mudou) cout << "\nCadastro alterado com sucesso!" << endl;
        }

        void remover() {
            system("cls");

            if (povo.empty()) {
                cout << "Nenhum registro cadastrado.\n";
                return;
            }

            int i = pesquisar();
            if (i < 0 || i >= (int)povo.size()) return;  

            string removido = povo[i]->nom();   
            delete povo[i];                     
            povo.erase(povo.begin() + i);        
            recalcularBest();
            cout << removido << " removido(a).\n";
        }

        void relatorio(){
            int receita=0, funcionarios=0, clientes=0, despesas=0;
            for (int i=0; i<(int)povo.size(); i++){
                if(povo[i]->tipo == '$'){
                    funcionario* f = dynamic_cast<funcionario*>(povo[i]);
                    funcionarios++;
                    despesas += f->salario;
                } else {
                    cliente* c = dynamic_cast<cliente*>(povo[i]);
                    clientes++;
                    receita += c->pagamento;
                }
            }
            system("cls");
            
            cout << "=== RELATORIO GERAL ===" << endl;
            cout << "Academia: " << nomeAcademia << endl;
            cout << "Endereco: " << endereco << endl;
            cout << "CNPJ: " << cnpj << endl;
            cout << "Data de Abertura: "; dataAbertura.mostrar(); cout << "\n\n";
            
            cout<< "Quantidade de funcionarios: "<< funcionarios<< endl;
            cout<< "Quantidade de clientes: "<< clientes<< endl;
            if (funcionario::best != nullptr)
                cout<< "Funcionario do mes: "<< funcionario::best->nome<< endl;
            else
                cout<< "Funcionario do mes: N/A"<< endl;
            cout<< "Receita total: "<< receita<< endl;
            cout<< "Despesas totais: "<< despesas<< endl;
            if (funcionarios > 0){
                cout<< "Receita media por funcionario: "<< receita/funcionarios<< endl;
                cout<< "Salario Medio: "<< despesas/funcionarios<< endl;
            }
            cout<< "Lucro: "<< receita-despesas<<endl;
        }

        ~crud(){
            arquivo.close();
            {
                ofstream out("registro.txt", ios::out | ios::trunc);
            }
            for(int i=0; i<(int)povo.size(); i++){
                povo[i]->arquivo();
            }
            for(int i=0; i<(int)povo.size(); i++){
                delete povo[i];
            }
            povo.clear();
        }
};
#endif