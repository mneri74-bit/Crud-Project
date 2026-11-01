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

// Legendas de cores
#define PRETO 0
#define AZUL_ESCURO 1
#define VERDE_ESCURO 2
#define CIANO_ESCURO 3
#define VERMELHO_ESCURO 4
#define ROXO 5
#define AMARELO_ESCURO 6
#define PADRAO 7
#define CINZA_ESCURO 8
#define AZUL_CLARO 9
#define VERDE_CLARO 10
#define CIANO_CLARO 11
#define VERMELHO_CLARO 12
#define ROSA_MAGENTA 13
#define AMARELO_CLARO 14
#define BRANCO 15

// Função nativa do Windows para colorir o texto
void textcolor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

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

        void cabecalho(string titulo){
            system("cls");
            textcolor(CIANO_CLARO);
            cout << "\n  === " << titulo << " ===\n\n";
            textcolor(PADRAO);
        }

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
            // Tenta ler a configuração salva
            string primeiraLinha;
            bool temConfig = false;
            
            if (arquivo.is_open()) {
                if (getline(arquivo, primeiraLinha) && primeiraLinha == "CONFIG") {
                    getline(arquivo, nomeAcademia);
                    getline(arquivo, endereco);
                    temConfig = true;
                }
            }

            // Se não achou configuração, pergunta e gera o CNPJ/Data
            if (!temConfig) {
                system("cls");
                textcolor(CIANO_CLARO);
                cout << "\n  === CONFIGURACAO INICIAL ===\n\n";
                textcolor(PADRAO);
                cout << "  Digite o nome da academia: ";
                getline(cin >> ws, nomeAcademia);
                cout << "  Digite o endereco da academia: ";
                getline(cin >> ws, endereco);
            }

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

            // Agora lê os registros de clientes e funcionários
            if (arquivo.is_open()) {
                if (!temConfig) {
                    // Se o arquivo existia mas não tinha a config (formato antigo), volta pro início
                    arquivo.clear();
                    arquivo.seekg(0);
                }
                
                char tipo;
                string nome, CPF;
                bool genero;
                int idade;
                float altura, peso;
                
                while (arquivo >> tipo) {
                    if (tipo == '$' || tipo == '#') { // Prevenção para não ler a linha "CONFIG" por engano
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
            }
            recalcularBest();
        }

        void listar(){
            cabecalho("LISTA DE REGISTROS");
            if(povo.empty()){
                textcolor(VERMELHO_CLARO);
                cout << "  Nenhum registro cadastrado.\n";
                textcolor(PADRAO);
                return;
            }
            for(int i=0; i<(int)povo.size(); i++){
                cout << "  [" << i+1 << "] " << povo[i]->nome;
                if(povo[i]->type()=='$'){ 
                    textcolor(AMARELO_CLARO);
                    cout << " (Funcionario)\n"; 
                    textcolor(PADRAO);
                }
                else{ 
                    textcolor(CIANO_CLARO);
                    cout << " (Cliente)\n"; 
                    textcolor(PADRAO);
                }
            }          
        }

        void exibir(){
            cabecalho("EXIBIR REGISTRO");
            if(povo.empty()){
                textcolor(VERMELHO_CLARO);
                cout << "  Nenhum registro cadastrado.\n";
                textcolor(PADRAO);
                return;
            }
            for(int i=0; i<(int)povo.size(); i++){
                cout << "  [" << i+1 << "] " << povo[i]->nome;
                if(povo[i]->type()=='$'){ cout << " (Funcionario)\n"; }
                else{ cout << " (Cliente)\n"; }
            }
            cout << "\n  Digite o numero (0 para cancelar): ";
            int input;
            cin >> input;
            if (!cin) { cin.clear(); cin.ignore(10000, '\n'); return; }
            if (input == 0) return;
            input--; 
            info(input);
        }

        void add(){
            cabecalho("INSERIR NOVO CADASTRO");
            int tipo = -1;
            do {
                cout << "  Qual tipo de cadastro?\n  [0] Cliente\n  [1] Funcionario\n  Opcao: ";
                cin >> tipo;
                if (!cin || (tipo != 0 && tipo != 1)) {
                    cin.clear(); cin.ignore(10000, '\n');
                    textcolor(VERMELHO_CLARO); cout << "  Opcao invalida, tente novamente!\n"; textcolor(PADRAO);
                }
            } while (!cin || (tipo != 0 && tipo != 1));
            cin.ignore();
            
            system("cls");
            textcolor(CIANO_CLARO);
            cout << "\n  === PREENCHIMENTO DE DADOS ===\n\n";
            textcolor(PADRAO);
            
            char barra;
            string nome, CPF;
            bool genero;
            int idade = 0;
            float altura = 0, peso = 0;
            
            if (tipo == 1){
                int salario = 0, dia = 0, mes = 0, ano = 0, g = -1;
                float rating = 0;
                string cargo;
                
                cout << "  Nome: "; getline(cin, nome);
                
                do {
                    cout << "  Idade: "; cin >> idade;
                    if (!cin || idade < 0 || idade > 120) {
                        cin.clear(); cin.ignore(10000, '\n');
                        textcolor(VERMELHO_CLARO); cout << "  Idade invalida, tente novamente!\n"; textcolor(PADRAO);
                    }
                } while (!cin || idade < 0 || idade > 120);
                cin.ignore();
                
                do {
                    cout << "  Genero (1-M / 0-F): "; cin >> g;
                    if (!cin || (g != 0 && g != 1)) {
                        cin.clear(); cin.ignore(10000, '\n');
                        textcolor(VERMELHO_CLARO); cout << "  Genero invalido, tente novamente!\n"; textcolor(PADRAO);
                    }
                } while (!cin || (g != 0 && g != 1));
                genero = (g == 1);
                cin.ignore();
                
                do {
                    cout << "  CPF: "; getline(cin, CPF);
                    if (cpfExiste(CPF)) {
                        textcolor(VERMELHO_CLARO); cout << "  CPF ja cadastrado, tente novamente!\n"; textcolor(PADRAO);
                    }
                } while (cpfExiste(CPF));
                
                do {
                    cout << "  Altura (ex: 1.75): "; cin >> altura;
                    if (!cin || altura <= 0) {
                        cin.clear(); cin.ignore(10000, '\n');
                        textcolor(VERMELHO_CLARO); cout << "  Altura invalida, tente novamente!\n"; textcolor(PADRAO);
                    }
                } while (!cin || altura <= 0);
                
                do {
                    cout << "  Peso (ex: 70.5): "; cin >> peso;
                    if (!cin || peso <= 0) {
                        cin.clear(); cin.ignore(10000, '\n');
                        textcolor(VERMELHO_CLARO); cout << "  Peso invalido, tente novamente!\n"; textcolor(PADRAO);
                    }
                } while (!cin || peso <= 0);
                cin.ignore();
                
                cout << "  Cargo: "; getline(cin, cargo);
                
                do {
                    cout << "  Salario: "; cin >> salario;
                    if (!cin || salario < 0) {
                        cin.clear(); cin.ignore(10000, '\n');
                        textcolor(VERMELHO_CLARO); cout << "  Salario invalido, tente novamente!\n"; textcolor(PADRAO);
                    }
                } while (!cin || salario < 0);
                
                do {
                    cout << "  Rating (0 a 10): "; cin >> rating;
                    if (!cin || rating < 0 || rating > 10) {
                        cin.clear(); cin.ignore(10000, '\n');
                        textcolor(VERMELHO_CLARO); cout << "  Rating deve ser entre 0 e 10, tente novamente!\n"; textcolor(PADRAO);
                    }
                } while (!cin || rating < 0 || rating > 10);
                
                do {
                    cout << "  Data Contratacao (dia/mes/ano): "; cin >> dia >> barra >> mes >> barra >> ano;
                    if (!cin || barra != '/' || dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900) {
                        cin.clear(); cin.ignore(10000, '\n');
                        textcolor(VERMELHO_CLARO); cout << "  Data invalida, tente novamente!\n"; textcolor(PADRAO);
                    }
                } while (!cin || barra != '/' || dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900);
                cin.ignore();
                
                povo.push_back(new funcionario(nome, genero, idade, altura, peso, CPF, cargo, salario, rating, dia, mes, ano));
            }else{
                int pagamento = 0, dia = 0, mes = 0, ano = 0, g = -1;
                string matricula;
                
                cout << "  Nome: "; getline(cin, nome);
                
                do {
                    cout << "  Idade: "; cin >> idade;
                    if (!cin || idade < 0 || idade > 120) {
                        cin.clear(); cin.ignore(10000, '\n');
                        textcolor(VERMELHO_CLARO); cout << "  Idade invalida, tente novamente!\n"; textcolor(PADRAO);
                    }
                } while (!cin || idade < 0 || idade > 120);
                cin.ignore();
                
                do {
                    cout << "  Genero (1-M / 0-F): "; cin >> g;
                    if (!cin || (g != 0 && g != 1)) {
                        cin.clear(); cin.ignore(10000, '\n');
                        textcolor(VERMELHO_CLARO); cout << "  Genero invalido, tente novamente!\n"; textcolor(PADRAO);
                    }
                } while (!cin || (g != 0 && g != 1));
                genero = (g == 1);
                cin.ignore();
                
                do {
                    cout << "  CPF: "; getline(cin, CPF);
                    if (cpfExiste(CPF)) {
                        textcolor(VERMELHO_CLARO); cout << "  CPF ja cadastrado, tente novamente!\n"; textcolor(PADRAO);
                    }
                } while (cpfExiste(CPF));
                
                do {
                    cout << "  Altura (ex: 1.75): "; cin >> altura;
                    if (!cin || altura <= 0) {
                        cin.clear(); cin.ignore(10000, '\n');
                        textcolor(VERMELHO_CLARO); cout << "  Altura invalida, tente novamente!\n"; textcolor(PADRAO);
                    }
                } while (!cin || altura <= 0);
                
                do {
                    cout << "  Peso (ex: 70.5): "; cin >> peso;
                    if (!cin || peso <= 0) {
                        cin.clear(); cin.ignore(10000, '\n');
                        textcolor(VERMELHO_CLARO); cout << "  Peso invalido, tente novamente!\n"; textcolor(PADRAO);
                    }
                } while (!cin || peso <= 0);
                cin.ignore();
                
                do {
                    cout << "  Pagamento Mensal: "; cin >> pagamento;
                    if (!cin || pagamento < 0) {
                        cin.clear(); cin.ignore(10000, '\n');
                        textcolor(VERMELHO_CLARO); cout << "  Pagamento invalido, tente novamente!\n"; textcolor(PADRAO);
                    }
                } while (!cin || pagamento < 0);
                
                do {
                    cout << "  Data Contrato (dia/mes/ano): "; cin >> dia >> barra >> mes >> barra >> ano;
                    if (!cin || barra != '/' || dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900) {
                        cin.clear(); cin.ignore(10000, '\n');
                        textcolor(VERMELHO_CLARO); cout << "  Data invalida, tente novamente!\n"; textcolor(PADRAO);
                    }
                } while (!cin || barra != '/' || dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900);
                cin.ignore();
                
                do {
                    cout << "  Matricula: "; getline(cin, matricula);
                    if (matriculaExiste(matricula)) {
                        textcolor(VERMELHO_CLARO); cout << "  Matricula ja cadastrada, tente novamente!\n"; textcolor(PADRAO);
                    }
                } while (matriculaExiste(matricula));
                
                povo.push_back(new cliente(nome, genero, idade, altura, peso, CPF, dia, mes, ano, pagamento, matricula));
            }
            recalcularBest();
            textcolor(VERDE_CLARO);
            cout << "\n  Cadastro realizado com sucesso!\n";
            textcolor(PADRAO);
        }

        void info(int input){
            system("cls");
            if(input >= 0 && input < (int)povo.size() ){
                textcolor(CIANO_CLARO);
                cout << "\n  === DETALHES DO REGISTRO ===\n\n";
                textcolor(PADRAO);
                povo[input]->print();
            }
        }

        int Pesquisar(string nome){
            string b = minusculo(nome);
            if (b.empty()){
                textcolor(VERMELHO_CLARO);
                cout << "  Busca vazia.\n";
                textcolor(PADRAO);
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
                textcolor(VERMELHO_CLARO);
                cout << "  Nenhum registro encontrado.\n";
                textcolor(PADRAO);
                return -1;
            }
            if(achados.size() == 1){
                return achados[0];
            }
            textcolor(AMARELO_CLARO);
            cout << "  Foram encontrados varios registros:\n";
            textcolor(PADRAO);
            cout << "  Escolha o numero (0 para cancelar): \n";
            for(int k=0; k<(int)achados.size(); k++){
                int i = achados[k];
                cout << "  [" << k+1 << "] ";
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
        
        void alterar(){
            cabecalho("ALTERAR REGISTRO");
            string busca;
            cout << "  Nome a pesquisar: ";
            getline(cin >> ws, busca);
            int idx = Pesquisar(busca);
            if(idx < 0) return;
            bool sair = false;
            bool mudou = false;
            while(!sair){
                system("cls");
                textcolor(CIANO_CLARO);
                cout << "\n  === ALTERANDO REGISTRO ===\n\n";
                textcolor(PADRAO);
                povo[idx]->print();
                textcolor(AMARELO_CLARO);
                cout << "\n  O que deseja alterar?\n";
                textcolor(PADRAO);
                cout << "  [1] Nome\n  [2] Idade\n  [3] Genero\n  [4] CPF\n  [5] Altura\n  [6] Peso\n  [7] Data\n";
                if(povo[idx]->tipo == '$'){
                    cout << "  [8] Salario\n  [9] Rating\n  [a] Cargo\n";
                } else {
                    cout << "  [8] Pagamento\n  [9] Matricula\n";}
                cout << "  [0] Salvar e sair\n\n  Opcao: ";
                char opc = getch();
                cout << opc << "\n";
                switch(opc){
                    case '1':
                        cout << "  Novo nome: ";
                        getline(cin >> ws, povo[idx]->nome);
                        mudou = true;
                        break;
                    case '2': {
                        do {
                            cout << "  Nova idade: "; cin >> povo[idx]->idade;
                            if (!cin || povo[idx]->idade < 0 || povo[idx]->idade > 120) {
                                cin.clear(); cin.ignore(10000, '\n');
                                textcolor(VERMELHO_CLARO); cout << "  Idade invalida, tente novamente!\n"; textcolor(PADRAO);
                            }
                        } while (!cin || povo[idx]->idade < 0 || povo[idx]->idade > 120);
                        cin.ignore();
                        mudou = true;
                        break;}
                    case '3': {
                        int g;
                        do {
                            cout << "  Novo genero (1-M / 0-F): "; cin >> g;
                            if (!cin || (g != 0 && g != 1)) {
                                cin.clear(); cin.ignore(10000, '\n');
                                textcolor(VERMELHO_CLARO); cout << "  Genero invalido, tente novamente!\n"; textcolor(PADRAO);
                            }
                        } while (!cin || (g != 0 && g != 1));
                        povo[idx]->genero = (g == 1);
                        cin.ignore();
                        mudou = true;
                        break;}
                    case '4': {
                        string novoCPF;
                        do {
                            cout << "  Novo CPF: "; getline(cin >> ws, novoCPF);
                            if (cpfExiste(novoCPF, idx)) {
                                textcolor(VERMELHO_CLARO); cout << "  CPF ja cadastrado, tente novamente!\n"; textcolor(PADRAO);
                            }
                        } while (cpfExiste(novoCPF, idx));
                        povo[idx]->CPF = novoCPF;
                        mudou = true;
                        break;}
                    case '5': {
                        float novaAltura;
                        do {
                            cout << "  Nova altura: "; cin >> novaAltura;
                            if (!cin || novaAltura <= 0) {
                                cin.clear(); cin.ignore(10000, '\n');
                                textcolor(VERMELHO_CLARO); cout << "  Altura invalida, tente novamente!\n"; textcolor(PADRAO);
                            }
                        } while (!cin || novaAltura <= 0);
                        povo[idx]->altura = novaAltura;
                        if(povo[idx]->tipo == '#') dynamic_cast<cliente*>(povo[idx])->calcularIMC();
                        mudou = true;
                        break;}
                    case '6': {
                        float novoPeso;
                        do {
                            cout << "  Novo peso: "; cin >> novoPeso;
                            if (!cin || novoPeso <= 0) {
                                cin.clear(); cin.ignore(10000, '\n');
                                textcolor(VERMELHO_CLARO); cout << "  Peso invalido, tente novamente!\n"; textcolor(PADRAO);
                            }
                        } while (!cin || novoPeso <= 0);
                        povo[idx]->peso = novoPeso;
                        if(povo[idx]->tipo == '#') dynamic_cast<cliente*>(povo[idx])->calcularIMC();
                        mudou = true;
                        break;}
                    case '7': {
                        int dia = 0, mes = 0, ano = 0;
                        char barra;
                        do {
                            cout << "  Nova data (dia/mes/ano): "; cin >> dia >> barra >> mes >> barra >> ano;
                            if (!cin || barra != '/' || dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900) {
                                cin.clear(); cin.ignore(10000, '\n');
                                textcolor(VERMELHO_CLARO); 
                                cout << "  Data invalida, tente novamente!\n"; 
                                textcolor(PADRAO);
                            }
                        } while (!cin || barra != '/' || dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900);
                        
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
                        cin.ignore();
                        mudou = true;
                        break;}
                    case '8': {
                        if(povo[idx]->tipo == '$'){
                            funcionario* f = dynamic_cast<funcionario*>(povo[idx]);
                            do {
                                cout << "  Novo salario: "; cin >> f->salario;
                                if (!cin || f->salario < 0) {
                                    cin.clear(); cin.ignore(10000, '\n');
                                    textcolor(VERMELHO_CLARO); cout << "  Salario invalido, tente novamente!\n"; textcolor(PADRAO);
                                }
                            } while (!cin || f->salario < 0);
                        } else {
                            cliente* c = dynamic_cast<cliente*>(povo[idx]);
                            do {
                                cout << "  Novo pagamento: "; cin >> c->pagamento;
                                if (!cin || c->pagamento < 0) {
                                    cin.clear(); cin.ignore(10000, '\n');
                                    textcolor(VERMELHO_CLARO); cout << "  Pagamento invalido, tente novamente!\n"; textcolor(PADRAO);
                                }
                            } while (!cin || c->pagamento < 0);
                        }
                        cin.ignore();
                        mudou = true;
                        break;}
                    case '9': {
                        if(povo[idx]->tipo == '$'){
                            funcionario* f = dynamic_cast<funcionario*>(povo[idx]);
                            do {
                                cout << "  Novo rating: "; cin >> f->rating;
                                if (!cin || f->rating < 0 || f->rating > 10) {
                                    cin.clear(); cin.ignore(10000, '\n');
                                    textcolor(VERMELHO_CLARO); cout << "  Rating deve ser entre 0 e 10, tente novamente!\n"; textcolor(PADRAO);
                                }
                            } while (!cin || f->rating < 0 || f->rating > 10);
                            recalcularBest();
                            mudou = true;
                        } else {
                            cliente* c = dynamic_cast<cliente*>(povo[idx]);
                            string novaMat;
                            do {
                                cout << "  Nova matricula: "; getline(cin >> ws, novaMat);
                                if (matriculaExiste(novaMat, idx)) {
                                    textcolor(VERMELHO_CLARO); cout << "  Matricula ja cadastrada, tente novamente!\n"; textcolor(PADRAO);
                                }
                            } while (matriculaExiste(novaMat, idx));
                            c->matricula = novaMat;
                            mudou = true;
                        }
                        cin.ignore();
                        break;}
                    case 'a': {
                        if(povo[idx]->tipo == '$'){
                            funcionario* f = dynamic_cast<funcionario*>(povo[idx]);
                            cout << "  Novo cargo: ";
                            getline(cin >> ws, f->cargo);
                            mudou = true;
                        }
                        break;}
                    case '0':
                        sair = true;
                        break;
                    default:
                        textcolor(VERMELHO_CLARO);
                        cout << "  Opcao invalida.\n";
                        textcolor(PADRAO);}
                Sleep(800);}
            if (mudou) {
                textcolor(VERDE_CLARO);
                cout << "\n  Cadastro alterado com sucesso!\n";
                textcolor(PADRAO);}
        }

        void remover() {
            cabecalho("REMOVER REGISTRO");
            if (povo.empty()) {
                textcolor(VERMELHO_CLARO);
                cout << "  Nenhum registro cadastrado.\n";
                textcolor(PADRAO);
                return;}
            string busca;
            cout << "  Nome a pesquisar: ";
            getline(cin >> ws, busca);
            int i = Pesquisar(busca);
            if (i < 0 || i >= (int)povo.size()) return;  
            string removido = povo[i]->nom();   
            delete povo[i];                     
            povo.erase(povo.begin() + i);        
            recalcularBest();
            textcolor(VERDE_CLARO);
            cout << "\n  " << removido << " removido(a) com sucesso!\n";
            textcolor(PADRAO);
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
            cabecalho("RELATORIO GERAL");
            textcolor(CIANO_CLARO); 
            cout << "  Academia: "; 
            textcolor(PADRAO); 
            cout << nomeAcademia << "\n";
            textcolor(CIANO_CLARO); 
            cout << "  Endereco: "; 
            textcolor(PADRAO); 
            cout << endereco << "\n";
            textcolor(CIANO_CLARO); 
            cout << "  CNPJ: "; 
            textcolor(PADRAO); 
            cout << cnpj << "\n";
            textcolor(CIANO_CLARO); 
            cout << "  Data de Abertura: "; 
            textcolor(PADRAO); 
            dataAbertura.mostrar(); 
            textcolor(CIANO_CLARO); 
            cout << "\n  -------------------------------------------------\n";
            textcolor(CIANO_CLARO);
            cout << "  Quantidade de funcionarios: "; 
            textcolor(PADRAO); 
            cout << funcionarios << "\n";
            textcolor(CIANO_CLARO); 
            cout << "  Quantidade de clientes: "; 
            textcolor(PADRAO); 
            cout << clientes << "\n";
            
            if (funcionario::best != nullptr) {
                textcolor(CIANO_CLARO); 
                cout << "  Funcionario do mes: "; 
                textcolor(PADRAO);
                cout << funcionario::best->nome << " (Rating: " << funcionario::best->rating << ")\n";
            } else {
                textcolor(CIANO_CLARO); 
                cout << "  Funcionario do mes: "; 
                textcolor(PADRAO); 
                cout << "N/A\n";
            }
            textcolor(CIANO_CLARO);
            cout << "  -------------------------------------------------\n";            
            textcolor(CIANO_CLARO);
            cout << "  Receita total: "; 
            textcolor(PADRAO); 
            cout << "R$ " << receita << "\n";
            textcolor(CIANO_CLARO); 
            cout << "  Despesas totais: "; 
            textcolor(PADRAO); 
            cout << "R$ " << despesas << "\n";
            
            if (funcionarios > 0){
                textcolor(CIANO_CLARO); 
                cout << "  Receita media por funcionario: "; 
                textcolor(PADRAO); 
                cout << "R$ " << receita/funcionarios << "\n";
                textcolor(CIANO_CLARO); 
                cout << "  Salario Medio: "; 
                textcolor(PADRAO); 
                cout << "R$ " << despesas/funcionarios << "\n";
            }
            if(receita - despesas >= 0) {
                textcolor(VERDE_CLARO); 
                cout << "  Lucro: "; 
                textcolor(PADRAO); 
                cout << "R$ " << receita-despesas << "\n";
            }else {
                textcolor(VERMELHO_CLARO); 
                cout << "  Prejuizo: "; 
                textcolor(PADRAO); 
                cout << "R$ " << receita-despesas << "\n";}
        }

                ~crud(){
            arquivo.close();
            ofstream out("registro.txt", ios::out | ios::trunc);
            out << "CONFIG" << endl;
            out << nomeAcademia << endl;
            out << endereco << endl;
            out.close();
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