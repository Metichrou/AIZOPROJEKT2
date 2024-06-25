#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include <vector>
#include <climits>
#include <iostream>
#include <chrono>
#include "ListaGraf.h"

class BellmanFord {
public:
    void BellmanFordMacierz(int wierzcholki, int krawedzie, int** tab, int start);
    void BellmanFordLista(int wierzcholki, int krawedzie, ListaGraf** lista, int start);

private:
    void printPath(std::vector<int>& poprzednik, int i);
};

#endif // BELLMANFORD_H
