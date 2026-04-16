#include <cmath>
#include "macierz.h"
#include <iostream>

using namespace std;

static int min_of_2(const int a, const int b);
static double wyznacznik_z_przekatnej(const Macierz& A);
static void gauss_croute(Macierz& A);
static void simple_method_buildup(Macierz& H, Macierz& G, double& max_suma);

double wyznacznik(Macierz A) {

	if (A.wiersze != A.kolumny or A.macierz == nullptr) {
		throw;
	}

	double znak = 1.0;
	gauss_croute(A);

	double det = znak;
	for (int i = 0; i < A.wiersze; i++) {
		det *= A.macierz[i][i];
	}

}

double norma_wektorowa(const Macierz& A) {
	if (A.macierz == nullptr or A.wiersze != 1 and A.kolumny != 1) {
		throw;
	}

	if (A.wiersze == 1 and A.kolumny == 1) {
		return A.macierz[0][0];
	}

	double suma = 0.0;
	if (A.wiersze == 1) {
		for (int i = 0; i < A.kolumny; i++) {
			suma += A.macierz[0][i]*A.macierz[0][i];
		}
		return sqrt(suma);
	}

	if (A.kolumny == 1) {
		for (int i = 0; i < A.wiersze; i++) {
			suma += A.macierz[i][0] * A.macierz[i][0];
		}
		return sqrt(suma);
	}
}

Macierz eliminacja_gaussa_croute(Macierz A_b, const Macierz& b, std::string nazwa) {
	if (A_b.macierz == nullptr or b.macierz == nullptr) {
		throw;
	}

	if (A_b.wiersze != A_b.kolumny or A_b.wiersze != b.wiersze or b.kolumny != 1) {
		throw;
	}
	
	double E = 1e-18;
	int A_rows = A_b.wiersze;

	A_b.doczep_kolumny(b);
	gauss_croute(A_b);

	Macierz x(A_rows,1, 0.0, nazwa);
	if (abs(wyznacznik_z_przekatnej(A_b)) < E) {
		cout << endl << "UWAGA! Uklad nie ma zadnych rozwiazan." << endl;
	}
	else {
		for (int i = A_rows; i >= 1; i--) {
			double suma = 0.0;
			for (int j = A_rows; j > i; j--) {
				suma += A_b.macierz[i-1][j-1] * x.macierz[j-1][0];
			}
			x.macierz[i - 1][0] = (A_b.macierz[i - 1][A_b.kolumny - 1] - suma) / A_b.macierz[i - 1][i - 1];
		}
	}
	return x;
}

Macierz metoda_jacobiego(Macierz H, Macierz G, const int k_max, std::string nazwa) {
	double E = 1e-8;
	int H_wiersze = H.wiersze; 
	double max_suma = simple_method_buildup(H, G);
	Macierz x_n(H_wiersze, 1, 0.0, nazwa);
	if (max_suma >= 1.0) {
		cout 
			<< endl 
			<< "Uwaga! Ciag wektorow rozwiazan nie bedzie zbiezny do rozwiazania dokladnego." 
			<< endl;
	}
	else {
		Macierz x_0;
		int k = 1;
		do {
			x_0 = x_n;
			for (int i = 0; i < H_wiersze; i++) {
				double suma = 0.0;
				for (int j = 0; j < H_wiersze; j++) {
					suma += x_0.macierz[j][0] * H.macierz[i][j];
				}
				x_n.macierz[i][0] = G.macierz[i][0] + suma;
			}
		} while (norma_wektorowa(x_n - x_0) >= E and k++ < k_max);
	}
	return x_n;
}


Macierz metoda_gaussa_siedla(Macierz H, Macierz G, const int k_max, std::string nazwa) {
	double E = 1e-8;
	double H_wiersze = H.wiersze;
	double max_suma = simple_method_buildup(H, G);
	Macierz x_n(H_wiersze, 1, 0.0, nazwa);
	if (max_suma >= 1.0) {
		cout
			<< endl
			<< "Uwaga! Ciag wektorow rozwiazan nie bedzie zbiezny do rozwiazania dokladnego."
			<< endl;
	}
	else {
		Macierz x_0;
		int k = 1;
		do {
			x_0 = x_n;
			for (int i = 0; i < H_wiersze; i++) {
				double suma = 0.0;
				for (int j = 0; j < H_wiersze; j++) {
					suma += x_n.macierz[j][0] * H.macierz[i][j];
				}
				x_n.macierz[i][0] = G.macierz[i][0] + suma;
			}
		} while (norma_wektorowa(x_n - x_0) >= E and k++ < k_max);
	}

	return x_n;
}

static int min_of_2(const int a, const int b) {
	return a < b ? a : b;
}

static double wyznacznik_z_przekatnej(const Macierz& A) {
	double wyznacznik = 1;
	int wiersze = A.wiersze;
	int kolumny = A.kolumny;

	int lower_size = min_of_2(wiersze, kolumny);
	for (int i = 0; i < lower_size; i++) {
		wyznacznik *= A.macierz[i][i];
	}

	return wyznacznik;
};

static void gauss_croute(Macierz& A) {

	double E = 1e-18;
	int A_rows = A.wiersze;

	for (int k = 1; k < A_rows; k++) {
		double max_wartosc = abs(A.macierz[k - 1][k - 1]);
		int max_wiersz = k;
		for (int i = k + 1; i <= A_rows; i++) {
			if (int wartosc = abs(A.macierz[i - 1][k - 1]); max_wartosc < wartosc) {
				max_wartosc = wartosc;
				max_wiersz = i;
			}
		}

		if (max_wartosc < E) {
			continue;
		}

		if (max_wiersz != k) {
			A.przestaw_wiersze(k, max_wiersz);
		}

		for (int i = k + 1; i <= A_rows; i++) {
			if (abs(A.macierz[i - 1][k - 1]) < E) {
				continue;
			}
			else {
				double m = A.macierz[i - 1][k - 1] / A.macierz[k - 1][k - 1];
				A.dodaj_wiersze(i, k, -m);
			}
		}
	}
}

static double simple_method_buildup(Macierz& H, Macierz& G) {
	if (H.macierz == nullptr or G.macierz == nullptr) {
		throw;
	}

	if (H.wiersze != H.kolumny or G.wiersze != H.wiersze or G.kolumny != 1) {
		throw;
	}

	double max_suma = 0.0;
	int H_wiersze = H.wiersze;
	for (int i = 1; i <= H_wiersze; i++) {
		G.macierz[i - 1][0] /= H.macierz[i - 1][i - 1];
		H.pomnoz_wiersz(i, -1.0 / H.macierz[i - 1][i - 1]);
		H.macierz[i - 1][i - 1] = 0.0;

		double suma = 0.0;
		for (int j = 0; j < H.wiersze; j++) {
			suma += abs(H.macierz[i - 1][i - 1]);
		}
		if (max_suma < suma) {
			max_suma = suma;
		}
	}
	return max_suma;
}
