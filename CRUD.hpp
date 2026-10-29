#ifndef crud_h
#define crud_h
#include <string>
#include <iostream>
#include <vector>
#include "pessoa.hpp"
#include "cliente.hpp"
#include "funcionário.hpp"


#include  <fstream>
using namespace std;
/*1. Inserir: cadastrar um novo registro.
2. Listar todos: exibir todos os registros cadastrados.
3. Exibir um: pesquisar e exibir um registro.
4. Alterar: pesquisar e modificar um registro.
5. Remover: pesquisar e excluir um registro.
6. Exibir relatório: apresentar um resumo dos dados.
7. Sair: encerrar o programa*/
class crud{
    private:
    
    public:
        fstream arquivo;
        static vector<pessoa*> povo;
        crud(): arquivo("registro.txt"){
            
            /*getline(arquivo, );
            do{

                getline(arquivo, );
            } while (rato!="$");*/
            }
        ~crud(){
             ofstream arquivo("registro.txt",ios::out);
            for(int i=0; i<povo.size(); i++){
                povo[i]->arquivo();
                }
            
        }
};
#endif