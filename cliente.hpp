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
        Data contrato;
        int pagamento;
        int diatreino, skip;
        float carga[3];
    public:
        cliente(string n, int i, float al, float p, string cpf, int dia, int mes, int ano,int pag, float c0=30, float c1=30, float c2=30)
        : pessoa(n, i, al, p, cpf), contrato(dia, mes, ano) {
            pagamento = pag;
            diatreino = 0;
            skip = 0;
            carga[0] = c0;
            carga[1] = c1;
            carga[2] = c2;
            tipo='#'; 
            }
        void treinar(char t){
            diatreino++;
            carga[t-'a'+1]+=1;
            peso -= 0.1;
            }
        void arquivo(){
            ofstream arquivo("registro.txt", ios::app);
            arquivo<< tipo;
            arquivo<< nome <<endl << idade<<endl << genero << endl<< CPF <<endl<< altura<< endl <<peso<< endl;
            arquivo<<diatreino <<endl<< skip <<endl<<pagamento<<endl<<contrato.dia<<endl<<contrato.mes<<endl<<contrato.ano<<endl;
            for(int i=0;i<3;i++){
                arquivo<<carga[i]<<endl;
            }
        }
        
};
#endif