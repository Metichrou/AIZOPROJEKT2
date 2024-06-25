#ifndef DANE_H
#define DANE_H

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "ListaGraf.h"

class Dane {
public:
    int** czytajMacierz(int& wierzcholki, int& krawedzie, int rodzaj_generacji, const std::string& nazwa);
    ListaGraf** czytajListaNaj(int& wierzcholki, int& krawedzie, const std::string& nazwa);
    ListaGraf** czytajListaMST(int& wierzcholki, int& krawedzie, const std::string& nazwa);
    int** generujMacierz(int& wierzcholki, int& krawedzie, int rodzaj_generacji);
    void wyswietl(int wierzcholki, int krawedzie, int** tab, ListaGraf** lista);
    void zapiszMST(int wierzcholki, int krawedzie, int** tab);
    void zapiszNaj(int wierzcholki, int krawedzie, int** tab);

private:
    bool sprawdz(int krawedzie, int** tab, int kra1, int kra2);
};

#endif // DANE_H
