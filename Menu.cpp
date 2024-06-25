#include "Menu.h"

void Menu::wyborProblemu() {
    int wybor;
    while (true) {
        std::cout << "Wybierz problem do rozwiazania" << std::endl;
        std::cout << "(1) Wyznaczanie minimalnego drzewa rozpinajacego" << std::endl;
        std::cout << "(2) Wyznaczanie najkrotszej sciezki w grafie" << std::endl;
        std::cin >> wybor;
        if (wybor == 1) {
            mst();
        } else if (wybor == 2) {
            najkrotszeSciezki();
        } else {
            std::cout << "Bledne dane" << std::endl;
        }
    }
}

void Menu::mst() {
    Prim prim;
    Kruskal kruskal;
    std::string nazwa;
    int wybor, wierzcholki = 0, krawedzie = 0;
    int** tab = nullptr;
    ListaGraf** lista = new ListaGraf * [wierzcholki]();

    while (true) {
        std::cout << "Wybierz algorytm rozwiazujacy problem" << std::endl;
        std::cout << "(1) Wczytaj z pliku" << std::endl;
        std::cout << "(2) Wygeneruj losowo" << std::endl;
        std::cout << "(3) Wyswietl" << std::endl;
        std::cout << "(4) Algorytm Prima (macierz)" << std::endl;
        std::cout << "(5) Algorytm Prima (lista)" << std::endl;
        std::cout << "(6) Algorytm Kruskala (macierz)" << std::endl;
        std::cout << "(7) Algorytm Kruskala (lista)" << std::endl;
        std::cout << "(8) Zakonczenie dzialania programu" << std::endl;
        std::cin >> wybor;
        switch (wybor) {
        case 1:
            std::cout << "Podaj nazwe pliku" << std::endl;
            std::cin >> nazwa;
            tab = dane.czytajMacierz(wierzcholki, krawedzie, 1, nazwa);
            if (!tab) {
                std::cout << "Niepoprawna nazwa pliku" << std::endl;
                break;
            }
            dane.zapiszMST(wierzcholki, krawedzie, tab);
            lista = dane.czytajListaMST(wierzcholki, krawedzie, "zapis.txt");
            break;
        case 2:
            tab = dane.generujMacierz(wierzcholki, krawedzie, 1);
            dane.zapiszMST(wierzcholki, krawedzie, tab);
            lista = dane.czytajListaMST(wierzcholki, krawedzie, "zapis.txt");
            break;
        case 3:
            dane.wyswietl(wierzcholki, krawedzie, tab, lista);
            break;
        case 4:
            prim.PrimMacierz(wierzcholki, krawedzie, tab);
            break;
        case 5:
            prim.PrimLista(wierzcholki, krawedzie, lista);
            break;
        case 6:
            kruskal.KruskalMacierz(wierzcholki, krawedzie, tab);
            break;
        case 7:
            kruskal.KruskalLista(wierzcholki, krawedzie, lista);
            break;
        case 8:
            return;
        default:
            std::cout << "Bledne dane" << std::endl;
            break;
        }
    }
}

void Menu::najkrotszeSciezki() {
    Dijkstra dijkstra;
    BellmanFord bellman;
    std::string nazwa;
    int wybor, wierzcholki = 0, krawedzie = 0;
    int** tab = nullptr;
    ListaGraf** lista = new ListaGraf * [wierzcholki]();

    while (true) {
        std::cout << "Wybierz algorytm rozwiazujacy problem" << std::endl;
        std::cout << "(1) Wczytaj z pliku" << std::endl;
        std::cout << "(2) Wygeneruj losowo" << std::endl;
        std::cout << "(3) Wyswietl" << std::endl;
        std::cout << "(4) Algorytm Dijkstry(macierz)" << std::endl;
        std::cout << "(5) Algorytm Dijkstry(lista)" << std::endl;
        std::cout << "(6) Algorytm Bellmana-Forda(macierz)" << std::endl;
        std::cout << "(7) Algorytm Bellmana-Forda(lista)" << std::endl;
        std::cout << "(8) Zakonczenie dzialania programu" << std::endl;
        std::cin >> wybor;
        switch (wybor) {
        case 1:
            std::cout << "Podaj nazwe pliku" << std::endl;
            std::cin >> nazwa;
            tab = dane.czytajMacierz(wierzcholki, krawedzie, -1, nazwa);
            if (!tab) {
                std::cout << "Niepoprawna nazwa pliku" << std::endl;
                break;
            }
            dane.zapiszNaj(wierzcholki, krawedzie, tab);
            lista = dane.czytajListaNaj(wierzcholki, krawedzie, "zapis.txt");
            break;
        case 2:
            tab = dane.generujMacierz(wierzcholki, krawedzie, -1);
            dane.zapiszNaj(wierzcholki, krawedzie, tab);
            lista = dane.czytajListaNaj(wierzcholki, krawedzie, "zapis.txt");
            break;
        case 3:
            dane.wyswietl(wierzcholki, krawedzie, tab, lista);
            break;
        case 4: {
            int start;
            std::cout << "Podaj wierzcholek poczatkowy: ";
            std::cin >> start;
            dijkstra.DijkstraMacierz(wierzcholki, krawedzie, tab, start);
            break;
        }
        case 5: {
            int start;
            std::cout << "Podaj wierzcholek poczatkowy: ";
            std::cin >> start;
            dijkstra.DijkstraLista(wierzcholki, krawedzie, lista, start);
            break;
        }
        case 6: {
            int start;
            std::cout << "Podaj wierzcholek poczatkowy: ";
            std::cin >> start;
            bellman.BellmanFordMacierz(wierzcholki, krawedzie, tab, start);
            break;
        }
        case 7: {
            int start;
            std::cout << "Podaj wierzcholek poczatkowy: ";
            std::cin >> start;
            bellman.BellmanFordLista(wierzcholki, krawedzie, lista, start);
            break;
        }
        case 8:
            return;
        default:
            std::cout << "Bledne dane" << std::endl;
            break;
        }
    }
}
