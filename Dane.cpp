#include "Dane.h"

int** Dane::czytajMacierz(int& wierzcholki, int& krawedzie, int rodzaj_generacji, const std::string& nazwa) {
    std::ifstream plik(nazwa);
    if (!plik.is_open()) {
        return nullptr;
    }
    plik >> krawedzie >> wierzcholki;
    int** tab = new int* [wierzcholki];
    for (int i = 0; i < wierzcholki; i++) {
        tab[i] = new int[krawedzie]();
    }
    for (int i = 0; i < krawedzie; i++) {
        int kra1, kra2, waga;
        plik >> kra1 >> kra2 >> waga;
        tab[kra1][i] = waga;
        tab[kra2][i] = waga * rodzaj_generacji;
    }
    return tab;
}

ListaGraf** Dane::czytajListaNaj(int& wierzcholki, int& krawedzie, const std::string& nazwa) {
    std::ifstream plik(nazwa);
    if (!plik.is_open()) {
        return nullptr;
    }
    plik >> krawedzie >> wierzcholki;
    ListaGraf** lista = new ListaGraf * [wierzcholki]();
    for (int i = 0; i < krawedzie; i++) {
        int kra1, kra2, waga;
        plik >> kra1 >> kra2 >> waga;
        auto* lista_wsk = new ListaGraf{ nullptr, kra2, waga };
        lista_wsk->next = lista[kra1];
        lista[kra1] = lista_wsk;
    }
    return lista;
}

ListaGraf** Dane::czytajListaMST(int& wierzcholki, int& krawedzie, const std::string& nazwa) {
    std::ifstream plik(nazwa);
    if (!plik.is_open()) {
        return nullptr;
    }
    plik >> krawedzie >> wierzcholki;
    ListaGraf** lista = new ListaGraf * [wierzcholki]();
    for (int i = 0; i < krawedzie; i++) {
        int kra1, kra2, waga;
        plik >> kra1 >> kra2 >> waga;
        auto* lista_wsk = new ListaGraf{ nullptr, kra2, waga };
        lista_wsk->next = lista[kra1];
        lista[kra1] = lista_wsk;
    }
    plik.clear();
    plik.seekg(0);
    plik >> krawedzie >> wierzcholki;
    for (int i = 0; i < krawedzie; i++) {
        int kra2, kra1, waga;
        plik >> kra2 >> kra1 >> waga;
        auto* lista_wsk = new ListaGraf{ nullptr, kra2, waga };
        lista_wsk->next = lista[kra1];
        lista[kra1] = lista_wsk;
    }
    return lista;
}

int** Dane::generujMacierz(int& wierzcholki, int& krawedzie, int rodzaj_generacji) {
    float gestosc;
    std::cout << "Podaj gestosc grafu w procentach: ";
    std::cin >> gestosc;
    gestosc /= 100.0;
    std::cout << "Podaj liczbe wierzcholkow: ";
    std::cin >> wierzcholki;
    krawedzie = gestosc * wierzcholki * (wierzcholki - 1) / 2;
    int** tab = new int* [wierzcholki];
    for (int i = 0; i < wierzcholki; i++) {
        tab[i] = new int[krawedzie]();
    }

    srand(time(0));
    for (int i = 0; i < wierzcholki - 1; i++) {
        int waga = rand() % INT_MAX + 1;
        tab[i][i] = waga;
        tab[i + 1][i] = waga * rodzaj_generacji;
    }

    for (int i = wierzcholki - 1; i < krawedzie; i++) {
        int kra1, kra2;
        do {
            kra1 = rand() % wierzcholki;
            do {
                kra2 = rand() % wierzcholki;
            } while (kra2 == kra1);
        } while (sprawdz(krawedzie, tab, kra1, kra2));

        int waga = rand() % INT_MAX + 1;
        int kolejnosc = rand() % 2;
        if (kolejnosc == 0) {
            tab[kra1][i] = waga;
            tab[kra2][i] = waga * rodzaj_generacji;
        } else {
            tab[kra1][i] = waga * rodzaj_generacji;
            tab[kra2][i] = waga;
        }
    }
    return tab;
}

void Dane::wyswietl(int wierzcholki, int krawedzie, int** tab, ListaGraf** lista) {
    std::cout << "Macierz: " << std::endl;
    for (int i = 0; i < wierzcholki; i++) {
        std::cout << i << ": ";
        for (int j = 0; j < krawedzie; j++) {
            std::cout << std::setw(8) << tab[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "Lista: " << std::endl;
    for (int i = 0; i < wierzcholki; i++) {
        std::cout << "A [" << i << "] =";
        for (ListaGraf* lista_wsk = lista[i]; lista_wsk; lista_wsk = lista_wsk->next) {
            std::cout << std::setw(3) << lista_wsk->v << std::setw(8) << lista_wsk->waga << ";";
        }
        std::cout << std::endl;
    }
}

void Dane::zapiszMST(int wierzcholki, int krawedzie, int** tab) {
    std::ofstream plik("zapis.txt");
    if (plik.is_open()) {
        plik << krawedzie << " " << wierzcholki << std::endl;
        for (int i = 0; i < krawedzie; i++) {
            int kra1 = -1, kra2 = -1, waga = 0;
            for (int j = 0; j < wierzcholki; j++) {
                if (tab[j][i] != 0) {
                    if (kra1 == -1) {
                        kra1 = j;
                        waga = tab[j][i];
                    } else {
                        kra2 = j;
                        plik << kra1 << " " << kra2 << " " << waga << std::endl;
                    }
                }
            }
        }
    } else {
        std::cout << "Nie mozna otworzyc pliku do zapisu: " << std::endl;
    }
}

void Dane::zapiszNaj(int wierzcholki, int krawedzie, int** tab) {
    std::ofstream plik("zapis.txt");
    if (plik.is_open()) {
        plik << krawedzie << " " << wierzcholki << std::endl;
        for (int i = 0; i < krawedzie; i++) {
            int kra1 = -1, kra2 = -1, waga = 0;
            for (int j = 0; j < wierzcholki; j++) {
                if (tab[j][i] != 0) {
                    if (kra1 == -1 && tab[j][i] > 0) {
                        kra1 = j;
                        waga = tab[j][i];
                    } else if (tab[j][i] < 0) {
                        kra2 = j;
                        plik << kra1 << " " << kra2 << " " << waga << std::endl;
                    }
                }
            }
        }
    } else {
        std::cout << "Nie mozna otworzyc pliku do zapisu: " << std::endl;
    }
}

bool Dane::sprawdz(int krawedzie, int** tab, int kra1, int kra2) {
    for (int i = 0; i < krawedzie; i++) {
        if ((tab[kra1][i] != 0 && tab[kra2][i] != 0) || (tab[kra1][i] != 0 && tab[kra2][i] != 0))
            return true;
    }
    return false;
}
