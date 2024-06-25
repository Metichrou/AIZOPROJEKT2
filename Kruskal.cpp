#include "Kruskal.h"
#include <iomanip>

void Kruskal::KruskalMacierz(int wierzcholki, int l_krawedzi, int** tab) {
    auto begin = std::chrono::high_resolution_clock::now();
    std::vector<Krawedz> krawedzie;

    for (int j = 0; j < l_krawedzi; j++) {
        int src = -1, dest = -1, weight = 0;
        for (int i = 0; i < wierzcholki; i++) {
            if (tab[i][j] != 0) {
                if (src == -1) {
                    src = i;
                    weight = tab[i][j];
                } else {
                    dest = i;
                    break;
                }
            }
        }
        if (src != -1 && dest != -1) {
            krawedzie.push_back({ src, dest, weight });
        }
    }

    std::sort(krawedzie.begin(), krawedzie.end(), [](Krawedz a, Krawedz b) {
        return a.waga < b.waga;
    });

    std::vector<Podzbior> podzbiory(wierzcholki);
    for (int v = 0; v < wierzcholki; ++v) {
        podzbiory[v].poprzednik = v;
        podzbiory[v].ranga = 0;
    }

    std::vector<Krawedz> wynik;
    int e = 0, i = 0;

    while (e < wierzcholki - 1 && i < krawedzie.size()) {
        Krawedz nastepna_krawedz = krawedzie[i++];
        int x = znajdz(podzbiory, nastepna_krawedz.pocz);
        int y = znajdz(podzbiory, nastepna_krawedz.kon);

        if (x != y) {
            wynik.push_back(nastepna_krawedz);
            zlacz(podzbiory, x, y);
            e++;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << "Krawedz Waga" << std::endl;
    for (auto& edge : wynik)
        std::cout << std::setw(3) << edge.pocz << ":" << edge.kon << std::setw(8) << edge.waga << std::endl;
    std::cout << "Czas wykonania: " << elapsed.count() << " ms" << std::endl;
}

void Kruskal::KruskalLista(int wierzcholki, int l_krawedzi, ListaGraf** lista) {
    auto begin = std::chrono::high_resolution_clock::now();
    std::vector<Krawedz> krawedzie;

    for (int u = 0; u < wierzcholki; ++u) {
        for (ListaGraf* pCrawl = lista[u]; pCrawl != nullptr; pCrawl = pCrawl->next) {
            if (u < pCrawl->v) {
                krawedzie.push_back({ u, pCrawl->v, pCrawl->waga });
            }
        }
    }

    std::sort(krawedzie.begin(), krawedzie.end(), [](Krawedz a, Krawedz b) {
        return a.waga < b.waga;
    });

    std::vector<Podzbior> podzbiory(wierzcholki);
    for (int v = 0; v < wierzcholki; ++v) {
        podzbiory[v].poprzednik = v;
        podzbiory[v].ranga = 0;
    }

    std::vector<Krawedz> wynik;

    for (Krawedz& e : krawedzie) {
        int x = znajdz(podzbiory, e.pocz);
        int y = znajdz(podzbiory, e.kon);
        if (x != y) {
            wynik.push_back(e);
            zlacz(podzbiory, x, y);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << "Krawedz Waga" << std::endl;
    for (Krawedz& e : wynik)
        std::cout << std::setw(3) << e.pocz << ":" << e.kon << std::setw(8) << e.waga << std::endl;
    std::cout << "Czas wykonania: " << elapsed.count() << " ms" << std::endl;
}

int Kruskal::znajdz(std::vector<Podzbior>& podzbiory, int i) {
    if (podzbiory[i].poprzednik != i)
        podzbiory[i].poprzednik = znajdz(podzbiory, podzbiory[i].poprzednik);
    return podzbiory[i].poprzednik;
}

void Kruskal::zlacz(std::vector<Podzbior>& podzbiory, int x, int y) {
    int xroot = znajdz(podzbiory, x);
    int yroot = znajdz(podzbiory, y);
    if (podzbiory[xroot].ranga < podzbiory[yroot].ranga)
        podzbiory[xroot].poprzednik = yroot;
    else if (podzbiory[xroot].ranga > podzbiory[yroot].ranga)
        podzbiory[yroot].poprzednik = xroot;
    else {
        podzbiory[yroot].poprzednik = xroot;
        podzbiory[xroot].ranga++;
    }
}
