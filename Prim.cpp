#include "Prim.h"
#include  <iomanip>
#include <queue>

void Prim::PrimMacierz(int wierzcholki, int krawedzie, int** tab) {
    auto begin = std::chrono::high_resolution_clock::now();
    std::vector<int> poprzednik(wierzcholki, -1);
    std::vector<int> key(wierzcholki, INT_MAX);
    std::vector<bool> wMST(wierzcholki, false);
    key[0] = 0;
    poprzednik[0] = -1;

    for (int i = 0; i < wierzcholki - 1; i++) {
        int u = minKey(key, wMST, wierzcholki);
        wMST[u] = true;

        for (int j = 0; j < krawedzie; j++) {
            if (tab[u][j] != 0) {
                int v = -1;
                int waga = tab[u][j];
                for (int k = 0; k < wierzcholki; k++) {
                    if (tab[k][j] != 0 && k != u) {
                        v = k;
                        break;
                    }
                }
                if (v != -1 && !wMST[v] && waga < key[v]) {
                    poprzednik[v] = u;
                    key[v] = waga;
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << "Krawedz Waga" << std::endl;
    for (int i = 1; i < wierzcholki; i++) {
        for (int j = 0; j < krawedzie; j++) {
            if (tab[i][j] != 0 && tab[poprzednik[i]][j] != 0) {
                std::cout << std::setw(3) << poprzednik[i] << ":" << i << std::setw(8) << tab[i][j] << std::endl;
            }
        }
    }
    std::cout << "Czas wykonania: " << elapsed.count() << " ms" << std::endl;
}

void Prim::PrimLista(int wierzcholki, int krawedzie, ListaGraf** lista) {
    auto begin = std::chrono::high_resolution_clock::now();
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    int start = 0;
    std::vector<int> key(wierzcholki, INT_MAX);
    std::vector<int> poprzednik(wierzcholki, -1);
    std::vector<bool> wMST(wierzcholki, false);

    pq.push(std::make_pair(0, start));
    key[start] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        wMST[u] = true;

        for (ListaGraf* pCrawl = lista[u]; pCrawl != nullptr; pCrawl = pCrawl->next) {
            int v = pCrawl->v;
            int weight = pCrawl->waga;

            if (!wMST[v] && key[v] > weight) {
                key[v] = weight;
                pq.push(std::make_pair(key[v], v));
                poprzednik[v] = u;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << "Krawedz Waga" << std::endl;
    for (int i = 1; i < wierzcholki; i++) {
        int u = poprzednik[i];
        for (ListaGraf* pCrawl = lista[u]; pCrawl != nullptr; pCrawl = pCrawl->next) {
            if (pCrawl->v == i) {
                std::cout << std::setw(3) << u << ":" << i << std::setw(8) << pCrawl->waga << std::endl;
                break;
            }
        }
    }
    std::cout << "Czas wykonania: " << elapsed.count() << " ms" << std::endl;
}

int Prim::minKey(std::vector<int>& key, std::vector<bool>& wMST, int wierzcholki) {
    int min = INT_MAX, min_index = 0;
    for (int v = 0; v < wierzcholki; v++) {
        if (!wMST[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}
