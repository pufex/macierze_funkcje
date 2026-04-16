#pragma once
#include "macierz.h"

class Macierze {
	
	int rozmiar;
	Macierz** tab_wsk;

	void dealokuj_macierze();
public:
	Macierze();
	Macierze(const Macierze& tablica);
	Macierze& operator=(const Macierze& tablica);
	~Macierze();

	void dorzuc(std::string nazwa = "");
	void dorzuc(int w, int k, std::string nazwa = "");
	void dorzuc(int w, int k, double wartosc, std::string nazwa = "");
	void dorzuc(const Macierz& A);

	void usun(int i);

	int n() const;
	Macierz& operator[](int k) const;

	friend std::ostream& operator<<(std::ostream& os, const Macierze& tablica);
};