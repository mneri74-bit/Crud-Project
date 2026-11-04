#ifndef pessoa_h
#define pessoa_h
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
using namespace std;
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

inline void textcolor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
class pessoa {
    friend class crud;
    protected:
        char tipo;
        bool genero;
        int idade;
        string nome, CPF;
        float altura, peso;
    public:
        pessoa(){}
        pessoa(string n,bool g, int i, float al, float p, string cpf) {
        nome = n;
        idade = i;
        altura = al;
        peso = p;
        CPF = cpf;
        genero = g;
        tipo = 'a';}
        char type(){
            return tipo;}
        string nom(){
            return nome;
        } 
        virtual void arquivo()=0;
        virtual void print() {
            textcolor(CIANO_CLARO);
            cout << (tipo == '$' ? "Funcionario" : "Cliente");
            textcolor(PADRAO);
            cout << " - " << nome << " - CPF: " << CPF << "\n";
            textcolor(AMARELO_CLARO); 
            cout << "Idade: "; 
            textcolor(PADRAO); 
            cout << idade<< endl;
            textcolor(AMARELO_CLARO); 
            cout << "Sexo: "; 
            textcolor(PADRAO); 
            if(genero) cout << "Masculino"; else{ cout << "Feminino"; }
            cout << "\n";
            textcolor(AMARELO_CLARO); 
            cout << "Altura: "; 
            textcolor(PADRAO); 
            cout << altura;
            cout << "\n";
            textcolor(AMARELO_CLARO); 
            cout << "Peso: "; 
            textcolor(PADRAO); 
            cout << peso << endl;
        }

        virtual ~pessoa() {}    
};

#endif