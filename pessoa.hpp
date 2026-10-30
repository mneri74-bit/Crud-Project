#ifndef pessoa_h
#define pessoa_h
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
using namespace std;
class pessoa {
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
            cout << "Pessoa - " << nome << " - CPF: " << CPF << "\nIdade: " << idade << "|| Sexo: ";
            if(genero) cout << "Masculino"; else{ cout << "Feminino"; }
            cout << "\nAltura: " << altura << " || Peso: " << peso << endl;
        }
        virtual ~pessoa() {}    
};

#endif
