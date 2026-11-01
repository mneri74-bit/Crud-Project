#ifndef funcionario_h
#define funcionario_h
#include <string>
#include <vector>
#include <iostream>
#include "pessoa.hpp"
#include "data.hpp"
#include  <fstream>

using namespace std;


class funcionario : public virtual pessoa {
    friend class crud;
    private:                    // ALTERADO: de protected para private (exigência da spec)
        string cargo;
        int salario;
        float rating;
        Data datadecontratacao;
        static funcionario* best;


    public:
        funcionario(string n,bool g, int i, float al, float p, string cpf,
                    string car, int sal, float rat, int dia, int mes, int ano)
        : pessoa(n,g, i, al, p, cpf){
            cargo = car;
            salario=sal;
            rating=rat;
            datadecontratacao.dia=dia; 
            datadecontratacao.mes=mes;
            datadecontratacao.ano=ano;
            tipo='$';
         }
        int getsalario(){
            return salario;
        }
        void arquivo(){
            ofstream arquivo("registro.txt", ios::app);
            arquivo<< tipo<< endl;
            arquivo<< nome <<endl << idade<<endl << genero << endl<< CPF <<endl<< altura<< endl <<peso<< endl;
            arquivo<< cargo << endl;
            arquivo<< salario<<endl<<rating<<endl<<datadecontratacao.dia<<endl<<datadecontratacao.mes<<endl<< datadecontratacao.ano<<endl;
            arquivo.close();
        }
        void print() override { 
            this->pessoa::print();
            cout << "Cargo: " << cargo << endl;
            cout << "Salario: " << salario << " || Rating: " << rating << endl;
            cout << "Data de contratacao: ";
            datadecontratacao.mostrar();
            cout << endl;
        }
        static funcionario* getGOAT(){ return best; }
};

inline funcionario* funcionario::best = nullptr;
#endif