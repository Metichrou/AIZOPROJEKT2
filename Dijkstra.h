#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <climits>
#include <iostream>
#include <chrono>
#include <queue>
#include "ListaGraf.h"

class Dijkstra {
public:
    void DijkstraMacierz(int wierzcholki, int krawedzie, int** tab, int start);
    void DijkstraLista(int wierzcholki, int krawedzie, ListaGraf** lista, int start);

private:
    int minDistance(std::vector<int>& dist, std::vector<bool>& visited, int wierzcholki);
    void printPath(std::vector<int>& poprzednik, int i);
};

#endif // DIJKSTRA_H
