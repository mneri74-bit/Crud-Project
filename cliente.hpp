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
        int diatreino, skip;
        float carga[3];
    public:
        cliente(string n,bool g, int i, float al, float p, string cpf, int dia, int mes, int ano,int pag, float c0=30, float c1=30, float c2=30, int dt=0, int sk=0)
        : pessoa(n,g, i, al, p, cpf), contratoprazo(dia, mes, ano) {
            pagamento = pag;
            diatreino = dt;
            skip = sk;
            carga[0] = c0;
            carga[1] = c1;
            carga[2] = c2;
            tipo='#'; 
            }
        void treinar(char t){
            carga[t-'a'+1]+=1;
            float saldo = diatreino - skip;       // >0 treinou mais, <0 faltou mais
            float a = 0.002;   // curvatura: quão rápido o ganho muscular acelera
            float b = 0.12;    // perda inicial por treino
            float d = diatreino - skip;           // treinos efetivos
            if(d < 0) d = 0;
            peso += a * (2*d + 1) - b;            // variação deste treino
            diatreino++;
            float minimo = 16 * altura * altura;  // limite de magreza grau III (IMC 16)
            if(peso < minimo){
                peso = minimo;
                }
        }
        void skipT(char t){
            skip++;
            carga[t-'a'+1]-=0.5; 
            float b = 0.12;    // perda inicial por treino
             float d = diatreino - skip;           // treinos efetivos
             if(d < 0) d = 0;
                peso +=  0.002 * (2*d + 1) - b;            // variação deste treino
                skip++;
                float minimo = 16 * altura * altura;  // limite de magreza grau III (IMC 16)
                if(peso < minimo){
                    peso = minimo;
                }
            }
        void arquivo(){
            ofstream arquivo("registro.txt", ios::app);
            arquivo<< tipo<< endl;
            arquivo<< nome <<endl << idade<<endl << genero << endl<< CPF <<endl<< altura<< endl <<peso<< endl;
            arquivo<<diatreino <<endl<< skip <<endl<<pagamento<<endl<<contratoprazo.dia<<endl<<contratoprazo.mes<<endl<<contratoprazo.ano<<endl;
            for(int i=0;i<3;i++){
                arquivo<<carga[i]<<endl;
            }
            arquivo.close();
        }
        void print(){
            int p=(int)((float)diatreino /(diatreino+skip) * 10000 + 0.5);
            cout<< "Cliente - "<< nome <<" - CPF: "<< CPF << "\nIdade: "<< idade<< "|| Sexo: ";
            if(genero) cout<< "M"; else{cout << "F";}
            cout<< "\nAltura: "<< altura<< " || Peso: "<< peso<< endl;
            cout<< "Presencas: "<< diatreino<< " || Faltas: "<< skip << " || Frequencia: "<< p /100 << "." << (p % 100 < 10 ? "0" : "") << p % 100 << "%" << endl;
            cout<< "Termos do contrato:\n Prazo de validade: "; contratoprazo.mostrar(); cout<< " Pagamento por mes: "<< pagamento<<endl;
            cout << "Cargas nos treinos:\nTreino A- Peitoral e Triceps: "<< carga[0]<<"\nTreino B- Costa e Biceps: "<< carga[1]<<"\nTreino C- Pernas: "<< carga[2];
        }
};
#endif