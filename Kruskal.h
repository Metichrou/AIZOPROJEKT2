#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include "ListaGraf.h"

class Kruskal {
public:
    void KruskalMacierz(int wierzcholki, int l_krawedzi, int** tab);
    void KruskalLista(int wierzcholki, int l_krawedzi, ListaGraf** lista);

private:
    struct Krawedz {
        int pocz, kon, waga;
    };

    struct Podzbior {
        int poprzednik;
        int ranga;
    };

    int znajdz(std::vector<Podzbior>& podzbiory, int i);
    void zlacz(std::vector<Podzbior>& podzbiory, int x, int y);
};

#endif // KRUSKAL_H
