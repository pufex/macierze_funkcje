#include "dynamiczne_macierze.h"

void Macierze::dealokuj_macierze() {
	if (tab_wsk != nullptr) {
		for (int i = 0; i < rozmiar; i++) {
			delete tab_wsk[i];
		}
		delete [] tab_wsk;
		rozmiar = 0;
		tab_wsk = nullptr;
	}
}

Macierze::Macierze(): rozmiar(0), tab_wsk(nullptr) {}

Macierze::Macierze(const Macierze& tablica): rozmiar(tablica.rozmiar), tab_wsk(rozmiar > 0 ? new Macierz*[rozmiar] : nullptr) {
	for (int i = 0; i < rozmiar; i++) {
		tab_wsk[i] = new Macierz(*tablica.tab_wsk[i]);
	}
}

Macierze& Macierze::operator=(const Macierze& tablica) {
	dealokuj_macierze();
	if (tablica.tab_wsk != nullptr) {
		rozmiar = tablica.rozmiar;
		tab_wsk = new Macierz *[rozmiar];
		for (int i = 0; i < rozmiar; i++) {
			tab_wsk[i] = new Macierz(*tablica.tab_wsk[i]);
		}
	}
	return *this;
}

Macierze::~Macierze() {
	if (tab_wsk != nullptr) {
		for (int i = 0; i < rozmiar; i++) {
			delete tab_wsk[i];
		}
		delete[] tab_wsk;
	}
}

void Macierze::dorzuc(std::string nazwa) {
	Macierz** nowa_tab_wsk = new Macierz * [rozmiar + 1];
	for (int i = 0; i < rozmiar; i++) {
		nowa_tab_wsk[i] = tab_wsk[i];
	}
	nowa_tab_wsk[rozmiar] = new Macierz(nazwa);
	if (tab_wsk != nullptr) {
		delete tab_wsk;
	}
	tab_wsk = nowa_tab_wsk;
	rozmiar += 1;
}

void Macierze::dorzuc(int w, int k, std::string nazwa) {
	Macierz** nowa_tab_wsk = new Macierz * [rozmiar + 1];
	for (int i = 0; i < rozmiar; i++) {
		nowa_tab_wsk[i] = tab_wsk[i];
	}
	nowa_tab_wsk[rozmiar] = new Macierz(w, k, nazwa);
	if (tab_wsk != nullptr) {
		delete tab_wsk;
	}
	tab_wsk = nowa_tab_wsk;
	rozmiar += 1;
}

void Macierze::dorzuc(int w, int k, double wartosc, std::string nazwa) {
	Macierz** nowa_tab_wsk = new Macierz * [rozmiar + 1];
	for (int i = 0; i < rozmiar; i++) {
		nowa_tab_wsk[i] = tab_wsk[i];
	}
	nowa_tab_wsk[rozmiar] = new Macierz(w, k, wartosc, nazwa);
	if (tab_wsk != nullptr) {
		delete tab_wsk;
	}
	tab_wsk = nowa_tab_wsk;
	rozmiar += 1;
}

void Macierze::dorzuc(const Macierz& A) {
	Macierz** nowa_tab_wsk = new Macierz * [rozmiar + 1];
	for (int i = 0; i < rozmiar; i++) {
		nowa_tab_wsk[i] = tab_wsk[i];
	}
	nowa_tab_wsk[rozmiar] = new Macierz(A, A.nazwa);
	if (tab_wsk != nullptr) {
		delete tab_wsk;
	}
	tab_wsk = nowa_tab_wsk;
	rozmiar += 1;
}

void Macierze::usun(int k) {
	if (k >= 0 and k < rozmiar) {
		rozmiar--;
		Macierz** nowa_tab_wsk = new Macierz * [rozmiar];
		int i = 0;
		int j = 0;
		while (j < rozmiar) {
			if (i != k) { 
				nowa_tab_wsk[j++] = tab_wsk[i];
			}
			i++;
		}
		delete tab_wsk[k];
		delete[] tab_wsk;
		tab_wsk = nowa_tab_wsk;
	}
}

int Macierze::n() const {
	return rozmiar;
}

Macierz& Macierze::operator[](int i) const {
	return *tab_wsk[i];
}

std::ostream& operator<<(std::ostream& os, const Macierze& tablica) {
	os << "=====================" << std::endl;
	for (int i = 0; i < tablica.rozmiar; i++) {
		os << *tablica.tab_wsk[i];
	}
	os << "=====================" << std::endl;
	return os;
}