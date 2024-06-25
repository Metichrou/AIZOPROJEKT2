#ifndef MENU_H
#define MENU_H

#include "Dane.h"
#include "Prim.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include "BellmanFord.h"

class Menu {
public:
    void wyborProblemu();

private:
    Dane dane;
    void mst();
    void najkrotszeSciezki();
};

#endif // MENU_H
