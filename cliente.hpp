#ifndef cliente_h
#define cliente_h
#include <string>
#include <iostream>
#include "pessoa.hpp"
#include "data.hpp"
using namespace std;

//1-braço 2-costas 3-pernas
class cliente : public virtual pessoa {
    protected:
        Data contratoprazo;
        int pagamento;
        string matricula;
        
    public:
        cliente(string n,bool g, int i, float al, float p, string cpf, int dia, int mes, int ano,int pag,string mat )
        : pessoa(n,g, i, al, p, cpf), contratoprazo(dia, mes, ano) {
            pagamento = pag;
            tipo='#'; 
            matricula=mat;
            }
    
        void arquivo(){
            ofstream arquivo("registro.txt", ios::app);
            arquivo<< tipo<< endl;
            arquivo<< nome <<endl << idade<<endl << genero << endl<< CPF <<endl<< altura<< endl <<peso<< endl;
            arquivo<<pagamento<<endl<<contratoprazo.dia<<endl<<contratoprazo.mes<<endl<<contratoprazo.ano<<endl;
            arquivo.close();
        }
        void print(){
            this->pessoa::print();
            cout<<"Matricula: "<< matricula<< "\nTermos do contrato:\nPrazo de validade: "; contratoprazo.mostrar(); cout<< "\nPagamento por mes: "<< pagamento<<endl;
        }
    };
#endif