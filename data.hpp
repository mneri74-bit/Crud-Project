#ifndef data_h
#define data_h
#include <iostream>
#include <string>

class Data {
public:
    int dia;
    int mes;
    int ano;

    Data(int d = 1, int m = 1, int a = 2000) {
        dia = d;
        mes = m;
        ano = a;
    }

    void mostrar() {
        std::cout << (dia < 10 ? "0" : "") << dia << "/"
                  << (mes < 10 ? "0" : "") << mes << "/"
                  << ano;
    }
};

#endif