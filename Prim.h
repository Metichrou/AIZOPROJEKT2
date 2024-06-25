#ifndef PRIM_H
#define PRIM_H

#include <vector>
#include <climits>
#include <iostream>
#include <chrono>
#include "ListaGraf.h"

class Prim {
public:
    void PrimMacierz(int wierzcholki, int krawedzie, int** tab);
    void PrimLista(int wierzcholki, int krawedzie, ListaGraf** lista);

private:
    int minKey(std::vector<int>& key, std::vector<bool>& wMST, int wierzcholki);
};

#endif // PRIM_H
