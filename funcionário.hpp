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
        funcionario(string n,string g, int i, float al, float p, string cpf, int sal, float rat, int dia, int mes, int ano): pessoa(n,g,  i, al, p, cpf){
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
            arquivo<< tipo<< endl;
            arquivo<< nome <<endl << idade<<endl << genero << endl<< CPF <<endl<< altura<< endl <<peso<< endl;
            arquivo<< salario<<endl<<rating<<endl<<datadecontratacao.dia<<endl<<datadecontratacao.mes<<endl<< datadecontratacao.ano;
            arquivo.close();
        }
        void print(){
            cout << "Funcionario - " << nome << " - CPF: " << CPF << "\nIdade: " << idade << "|| Sexo: ";
            if(genero) cout << "M"; else{ cout << "F"; }
            cout << "\nAltura: " << altura << " || Peso: " << peso << endl;
            cout << "Salario: " << salario << " || Rating: " << rating << endl;
            cout << "Data de contratacao: ";
            datadecontratacao.mostrar();
            cout << endl;
}
};
#endif
