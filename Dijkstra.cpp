#include "Dijkstra.h"
#include <iomanip>

void Dijkstra::DijkstraMacierz(int wierzcholki, int krawedzie, int** tab, int start) {
    auto begin = std::chrono::high_resolution_clock::now();
    std::vector<int> dist(wierzcholki, INT_MAX);
    std::vector<int> poprzednik(wierzcholki, -1);
    std::vector<bool> visited(wierzcholki, false);
    dist[start] = 0;

    for (int count = 0; count < wierzcholki - 1; count++) {
        int u = minDistance(dist, visited, wierzcholki);
        visited[u] = true;

        for (int j = 0; j < krawedzie; j++) {
            if (tab[u][j] > 0) {
                int v = -1;
                int waga = tab[u][j];
                for (int i = 0; i < wierzcholki; i++) {
                    if (tab[i][j] < 0 && i != u) {
                        v = i;
                        waga = -tab[i][j];
                        break;
                    }
                }
                if (v != -1 && !visited[v] && dist[u] != INT_MAX && dist[u] + waga < dist[v]) {
                    dist[v] = dist[u] + waga;
                    poprzednik[v] = u;
                }
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

void Dijkstra::DijkstraLista(int wierzcholki, int krawedzie, ListaGraf** lista, int start) {
    auto begin = std::chrono::high_resolution_clock::now();
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    std::vector<int> dist(wierzcholki, INT_MAX);
    std::vector<int> poprzednik(wierzcholki, -1);
    pq.push(std::make_pair(0, start));
    dist[start] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (ListaGraf* pCrawl = lista[u]; pCrawl != nullptr; pCrawl = pCrawl->next) {
            int v = pCrawl->v;
            int weight = pCrawl->waga;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push(std::make_pair(dist[v], v));
                poprzednik[v] = u;
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

int Dijkstra::minDistance(std::vector<int>& dist, std::vector<bool>& visited, int wierzcholki) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < wierzcholki; v++)
        if (!visited[v] && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void Dijkstra::printPath(std::vector<int>& poprzednik, int i) {
    if (poprzednik[i] == -1) {
        return;
    }
    printPath(poprzednik, poprzednik[i]);
    std::cout << poprzednik[i] << " ";
}
