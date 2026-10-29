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
        bool genero;
        int idade;
        string nome, CPF;
        float altura, peso;
    public:
        pessoa(){}
        pessoa(string n, int i, float al, float p, string cpf) {
        nome = n;
        idade = i;
        altura = al;
        peso = p;
        CPF = cpf;}
        void comer() {
            cout << "comida boa!, espero que eu nao engorde\n";
            Sleep(500);
            if(rand() % 2) {
            cout << nome <<"ganhou peso\n";
            peso += 0.1f;}   
        }
        char type(){
            return tipo;
        } 
        virtual void arquivo()=0;
};
#endif