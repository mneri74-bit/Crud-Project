#ifndef pessoa_h
#define pessoa_h
#include <string>
#include <iostream>
#include<fstream>
#include <windows.h>
using namespace std;
class pessoa {
    protected:
        char tipo;
        string genero;
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
        tipo = 0;}
        void comer() {
            cout << "comida boa!, espero que eu nao engorde\n";
            Sleep(500);
            if(rand() % 2) {
            cout << nome <<"ganhou peso\n";
            peso += 0.1f;}   
        }
        char type(){
            return tipo;}
        string nom(){
            return nome;
        } 
        virtual void arquivo()=0;
        virtual void print() {
            cout << "Pessoa - " << nome << " - CPF: " << CPF << "\nIdade: " << idade << "|| Sexo: ";
            if(genero) cout << "M"; else{ cout << "F"; }
            cout << "\nAltura: " << altura << " || Peso: " << peso << endl;
            cout << "Salario: " << salario << " || Rating: " << rating << endl;
            cout << "Data de contratacao: ";
            datadecontratacao.mostrar();
            cout << endl;;
};

#endif
