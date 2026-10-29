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
    protected:
        int salario;
        float rating;
        Data datadecontratacao;
        static funcionario* best;
        

    public:
        funcionario(string n, int i, float al, float p, string cpf, int sal, float rat, int dia, int mes, int ano): pessoa(n, i, al, p, cpf){
            salario=sal;
            rating=rat;
            datadecontratacao.dia=dia; 
            datadecontratacao.mes=mes;
            datadecontratacao.ano=ano;
            if(!best || best->rating<rat){
                best=this;
            }
            tipo='$';
         }
        int getsalarioanual(){
            return salario*12;
        }
        void arquivo(){
            ofstream arquivo("registro.txt", ios::app);
            arquivo<< tipo;
            arquivo<< nome <<endl << idade<<endl << genero << endl<< CPF <<endl<< altura<< endl <<peso<< endl;
            arquivo<< salario<<endl<<rating<<endl<<datadecontratacao.dia<<endl<<datadecontratacao.mes<<endl<< datadecontratacao.ano;
        }
};
#endif