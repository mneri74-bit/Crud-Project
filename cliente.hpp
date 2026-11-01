#ifndef cliente_h
#define cliente_h
#include <string>
#include <iostream>
#include <cmath>
#include "pessoa.hpp"
#include "data.hpp"
using namespace std;

class cliente : public virtual pessoa {
    friend class crud;
    private:
        Data contratoprazo;
        int pagamento;
        string matricula;
        float IMC;

        void calcularIMC() {
            IMC = (altura > 0) ? peso / (altura * altura) : 0;
        }

    public:
        cliente(string n,bool g, int i, float al, float p, string cpf, int dia, int mes, int ano,int pag,string mat )
        : pessoa(n,g, i, al, p, cpf), contratoprazo(dia, mes, ano) {
            pagamento = pag;
            tipo='#'; 
            matricula=mat;
            calcularIMC();
        }

        int getPagamento() { return pagamento; }
        string getMatricula() { return matricula; }
        float getIMC() { return IMC; }

        void arquivo(){
            ofstream arquivo("registro.txt", ios::app);
            arquivo<< tipo<< endl;
            arquivo<< nome <<endl << idade<<endl << genero << endl<< CPF <<endl<< altura<< endl <<peso<< endl;
            arquivo<<pagamento<<endl<<contratoprazo.dia<<endl<<contratoprazo.mes<<endl<<contratoprazo.ano<<endl;
            arquivo<<matricula<<endl;
            arquivo.close();
        }
        void print() override {
            this->pessoa::print();
            cout<<"IMC: "<< round(IMC * 10) / 10 << endl;
            cout<<"Matricula: "<< matricula<< "\nTermos do contrato:\nPrazo de validade: "; contratoprazo.mostrar(); cout<< "\nPagamento por mes: "<< pagamento<<endl;
        }
};
#endif