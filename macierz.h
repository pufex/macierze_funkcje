#pragma once

#include <iostream>
#include <cstring>


class Macierz {
	int wiersze;
	int kolumny;
	double** macierz;

	void dealokuj_macierz();
public:

	std::string nazwa;

	Macierz(std::string nazwa = "");
	Macierz(int w, int k, std::string nazwa = "");
	Macierz(int w, int k, double v, std::string nazwa = "");
	Macierz(const Macierz& B, std::string nazwa = "");
	Macierz& operator=(const Macierz& B);
	~Macierz();

	int daj_wiersze() const;
	int daj_kolumny() const;

	double& operator()(int w, int k);
	
	friend std::ostream& operator<<(std::ostream& os, const Macierz& A);

	void przestaw_wiersze(int w_1, int w_2);
	void pomnoz_wiersz(int w, double m);
	void dodaj_wiersze(int w_1, int w_2, double m = 1.0);

	void doczep_kolumny(const Macierz& K);
	void doczep_wiersze(const Macierz& W);

	friend Macierz operator+(const Macierz& A, const Macierz& B);
	friend Macierz operator-(const Macierz& A, const Macierz& B);
	friend Macierz operator*(const Macierz& A, const Macierz& B);

	friend double wyznacznik_z_przekatnej(const Macierz& A);
	friend void gauss_croute(Macierz& A);
	friend double simple_method_buildup(Macierz& H, Macierz& G);

	friend double wyznacznik(Macierz A);
	friend double norma_wektorowa(const Macierz& A);
	friend Macierz eliminacja_gaussa_croute(Macierz A, const Macierz& b, std::string nazwa = "x");
	friend Macierz metoda_jacobiego(Macierz A, Macierz b, const int k_max, std::string nazwa = "x");
	friend Macierz metoda_gaussa_siedla(Macierz A, Macierz b, const int k_max, std::string nazwa = "x");
};

