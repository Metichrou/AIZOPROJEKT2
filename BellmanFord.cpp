#include "BellmanFord.h"
#include <iomanip>

void BellmanFord::BellmanFordMacierz(int wierzcholki, int krawedzie, int** tab, int start) {
    auto begin = std::chrono::high_resolution_clock::now();
    std::vector<int> dist(wierzcholki, INT_MAX);
    std::vector<int> poprzednik(wierzcholki, -1);
    dist[start] = 0;

    for (int i = 1; i <= wierzcholki - 1; ++i) {
        for (int j = 0; j < krawedzie; ++j) {
            int u = -1, v = -1, waga = 0;
            for (int k = 0; k < wierzcholki; ++k) {
                if (tab[k][j] > 0) {
                    u = k;
                    waga = tab[k][j];
                } else if (tab[k][j] < 0) {
                    v = k;
                }
            }
            if (u != -1 && v != -1 && dist[u] != INT_MAX && dist[u] + waga < dist[v]) {
                dist[v] = dist[u] + waga;
                poprzednik[v] = u;
            }
        }
    }

    for (int j = 0; j < krawedzie; ++j) {
        int u = -1, v = -1, waga = 0;
        for (int k = 0; k < wierzcholki; ++k) {
            if (tab[k][j] > 0) {
                u = k;
                waga = tab[k][j];
            } else if (tab[k][j] < 0) {
                v = k;
            }
        }
        if (u != -1 && v != -1 && dist[u] != INT_MAX && dist[u] + waga < dist[v]) {
            std::cout << "Graf zawiera cykl o ujemnej wadze" << std::endl;
            return;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "Wierzcholek    Odleglosc od startu    Sciezka" << std::endl;
    for (int i = 0; i < wierzcholki; ++i) {
        std::cout << std::setw(5) << i << std::setw(20);
        if (dist[i] == INT_MAX) {
            std::cout << "brak sciezki";
        } else {
            std::cout << dist[i] << "    ";
            printPath(poprzednik, i);
        }
        std::cout << std::endl;
    }
    std::cout << "Czas wykonania: " << elapsed.count() << " ms" << std::endl;
}

void BellmanFord::BellmanFordLista(int wierzcholki, int krawedzie, ListaGraf** lista, int start) {
    auto begin = std::chrono::high_resolution_clock::now();
    std::vector<int> dist(wierzcholki, INT_MAX);
    std::vector<int> poprzednik(wierzcholki, -1);
    dist[start] = 0;

    for (int i = 1; i <= wierzcholki - 1; i++) {
        for (int u = 0; u < wierzcholki; u++) {
            for (ListaGraf* pCrawl = lista[u]; pCrawl != nullptr; pCrawl = pCrawl->next) {
                int v = pCrawl->v;
                int weight = pCrawl->waga;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    poprzednik[v] = u;
                }
            }
        }
    }

    for (int u = 0; u < wierzcholki; u++) {
        for (ListaGraf* pCrawl = lista[u]; pCrawl != nullptr; pCrawl = pCrawl->next) {
            int v = pCrawl->v;
            int weight = pCrawl->waga;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                std::cout << "Graf zawiera cykl o ujemnej wadze" << std::endl;
                return;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "Wierzcholek    Odleglosc od startu    Sciezka" << std::endl;
    for (int i = 0; i < wierzcholki; i++) {
        std::cout << std::setw(5) << i << std::setw(20);
        if (dist[i] == INT_MAX) {
            std::cout << "brak sciezki";
        } else {
            std::cout << dist[i] << "    ";
            printPath(poprzednik, i);
        }
        std::cout << std::endl;
    }
    std::cout << "Czas wykonania: " << elapsed.count() << " ms" << std::endl;
}

void BellmanFord::printPath(std::vector<int>& poprzednik, int i) {
    if (poprzednik[i] == -1) {
        return;
    }
    printPath(poprzednik, poprzednik[i]);
    std::cout << poprzednik[i] << " ";
}
