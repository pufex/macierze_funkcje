#include "macierz.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void Macierz::dealokuj_macierz() {
	if (macierz != nullptr) {
		for (int i = 0; i < wiersze; i++) {
			delete[] macierz[i];
		}
		delete[] macierz;
		macierz = nullptr;
		wiersze = 0;
		kolumny = 0;
	}
}

Macierz::Macierz(std::string tekst): wiersze(0), kolumny(0), macierz(nullptr), nazwa(tekst) {}

Macierz::Macierz(int w, int k, std::string tekst): wiersze(w), kolumny(k), macierz(w > 0 and k > 0 ? new double*[w] : nullptr), nazwa(tekst) {
	if (macierz != nullptr) {
		for (int i = 0; i < wiersze; i++) {
			macierz[i] = new double[kolumny];
		}
	}else {
		wiersze = 0;
		kolumny = 0;
	}
}

Macierz::Macierz(int w, int k, double v, std::string tekst): wiersze(w), kolumny(k), macierz(w > 0 and k > 0 ? new double*[w] : nullptr), nazwa(tekst) {
	if (macierz != nullptr) {
		for (int i = 0; i < wiersze; i++) {
			macierz[i] = new double[kolumny];
			for (int j = 0; j < kolumny; j++) {
				macierz[i][j] = v;
			}
		}
	}
	else {
		wiersze = 0;
		kolumny = 0;
	}
}

Macierz::Macierz(const Macierz& B, std::string tekst): wiersze(B.wiersze), kolumny(B.kolumny), macierz(wiersze > 0 and kolumny > 0 ? new double*[wiersze] : nullptr), nazwa(tekst) {
	if (macierz != nullptr) {
		for (int i = 0; i < wiersze; i++) {
			macierz[i] = new double[kolumny];
			for (int j = 0; j < kolumny; j++) {
				macierz[i][j] = B.macierz[i][j];
			}
		}
	}
	else {
		wiersze = 0;
		kolumny = 0;
	}
}

Macierz& Macierz::operator=(const Macierz& B) {
	dealokuj_macierz();
	if (B.macierz != nullptr) {
		nazwa = B.nazwa;
		wiersze = B.wiersze;
		kolumny = B.kolumny;
		macierz = new double*[wiersze];
		for (int i = 0; i < wiersze; i++) {
			macierz[i] = new double[kolumny];
			for (int j = 0; j < kolumny; j++) {
				macierz[i][j] = B.macierz[i][j];
			}
		}
	}
	return *this;
}

Macierz::~Macierz() {
	if (macierz != nullptr) {
		for (int i = 0; i < wiersze; i++) {
			delete[] macierz[i];
		}
		delete[] macierz;
	}
}

int Macierz::daj_wiersze() const{
	return wiersze;
}

int Macierz::daj_kolumny() const {
	return kolumny;
}

double& Macierz::operator()(int w, int k) {
	if (w > wiersze or w <= 0 or k > kolumny or k <= 0) {
		throw;
	}
	return macierz[w - 1][k - 1];
}

std::ostream& operator<<(std::ostream& os, const Macierz& A) {
	os << endl;
	os << A.nazwa << " = " << std::endl;
	for (int i = 0; i < A.wiersze; i++) {
		os <<  "\t| ";
		for (int j = 0; j < A.kolumny; j++) {
			os
				<< setprecision(5)
				<< setw(9)
				<< fixed
				<< A.macierz[i][j]
				<< " ";
		}
		os << "|" << endl;
	}
	os << endl;
	
	return os;
}

void Macierz::przestaw_wiersze(int w_1, int w_2) {
	if (w_1 <= 0 or w_1 > wiersze or w_2 <= 0 or w_2 > wiersze) {
		throw;
	}

	double* temp = macierz[w_1 - 1];
	macierz[w_1 - 1] = macierz[w_2 - 1];
	macierz[w_2 - 1] = temp;
}

void Macierz::pomnoz_wiersz(int w, double m) {

	if (w <= 0 or w > wiersze) {
		throw;
	}

	for (int i = 0; i < kolumny; i++) {
		macierz[w - 1][i] *= m;
	}
}

void Macierz::dodaj_wiersze(int w_1, int w_2, double m) {
	if (w_1 <= 0 or w_1 > wiersze or w_2 <= 0 or w_2 > wiersze) {
		throw;
	}

	for (int i = 0; i < kolumny; i++) {
		macierz[w_1 - 1][i] += m*macierz[w_2 - 1][i];
	}
}


void Macierz::doczep_kolumny(const Macierz& K) {
	if (K.macierz == nullptr or K.wiersze < wiersze) {
		throw;
	}

	int nowe_kolumny = kolumny + K.kolumny;
	int nowe_wiersze = wiersze;
	double** nowa_macierz = new double* [wiersze];
	for (int i = 0; i < wiersze; i++) {
		nowa_macierz[i] = new double[nowe_kolumny];
		for (int j = 0; j < kolumny; j++) {
			nowa_macierz[i][j] = macierz[i][j];
		}

		for (int j = kolumny; j < nowe_kolumny; j++) {
			nowa_macierz[i][j] = K.macierz[i][j-kolumny];
		}
	}

	dealokuj_macierz();

	macierz = nowa_macierz;
	wiersze = nowe_wiersze;
	kolumny = nowe_kolumny;
}

void Macierz::doczep_wiersze(const Macierz& W) {

	if (W.macierz == nullptr or W.kolumny < kolumny) {
		throw;
	}

	int nowe_wiersze = wiersze + W.wiersze;
	double** nowa_macierz = new double* [nowe_wiersze];

	for (int i = 0; i < wiersze; i++) {
		nowa_macierz[i] = macierz[i];
	}

	for (int i = wiersze; i < nowe_wiersze; i++) {
		nowa_macierz[i] = new double[kolumny];
		for (int j = 0; j < kolumny; j++) {
			nowa_macierz[i][j] = W.macierz[i - wiersze][j];
		}
	}

	delete[] macierz;
	macierz = nowa_macierz;
	wiersze = nowe_wiersze;
}

Macierz operator+(const Macierz& A, const Macierz& B) {
	if (A.macierz == nullptr or B.macierz == nullptr) {
		throw;
	}
	else if (A.wiersze != B.wiersze or A.kolumny != B.kolumny) {
		throw;
	}

	int wiersze = A.wiersze;
	int kolumny = A.kolumny;
	Macierz C(wiersze, kolumny);
	for (int i = 0; i < wiersze; i++) {
		for (int j = 0; j < kolumny; j++) {
			C.macierz[i][j] = A.macierz[i][j] + B.macierz[i][j];
		}
	}
	
	return C;
}

Macierz operator-(const Macierz& A, const Macierz& B) {
	if (A.macierz == nullptr or B.macierz == nullptr) {
		throw;
	}
	else if (A.wiersze != B.wiersze or A.kolumny != B.kolumny) {
		throw;
	}

	int wiersze = A.wiersze;
	int kolumny = A.kolumny;
	Macierz C(wiersze, kolumny);
	for (int i = 0; i < wiersze; i++) {
		for (int j = 0; j < kolumny; j++) {
			C.macierz[i][j] = A.macierz[i][j] - B.macierz[i][j];
		}
	}

	return C;
}


Macierz operator*(const Macierz& A, const Macierz& B) {
	if (A.macierz == nullptr or B.macierz == nullptr) {
		throw;
	}
	else if (A.kolumny != B.wiersze) {
		throw;
	}

	int wiersze = A.wiersze;
	int kolumny = B.kolumny;
	Macierz C(wiersze, kolumny);
	for (int i = 0; i < wiersze; i++) {
		for (int j = 0; j < kolumny; j++) {
			double suma = 0.0;
			for (int k = 0; k < A.kolumny; k++) {
				suma += A.macierz[i][k] * B.macierz[k][j];
			}
			C.macierz[i][j] = suma;
		}
	}
	return C;
}
