#include "dynamiczne_macierze.h"
#include "macierz_interfejs.h"
#include "macierz_globalne.h"
#include <iostream>
#include <conio.h>

using namespace std;

static Macierz kreator_macierzy();
static void wymien_macierze();

static void menu_macierzy();

static void wyswietl_macierze();
static void dodaj_macierz();
static void usun_macierz();

static void menu_funkcji();

static void wybierz_macierze_ukladu(int& i_A, int& i_b);

static void wykonaj_eliminacje_gaussa_crouta();
static void wykonaj_metode_jacobiego();
static void wykonaj_metode_gaussa_siedla();

void menu_glowne() {
	int wybor;
	do{
		system("cls");
		cout
			<< "Menu Glowne: " << endl
			<< endl
			<< "0. Zakoncz" << endl
			<< endl
			<< "1. Macierze" << endl
			<< "2. Funkcje" << endl
			<< endl
			<< "Wybor: ";
		cin >> wybor;

		switch (wybor) {
			case 1:
				menu_macierzy();
				break;
			case 2:
				menu_funkcji();
				break;
			default: break;
		}
	} while (wybor != 0);
}


static Macierz kreator_macierzy() {
	system("cls");
	cout << "UWAGA! Wprowadzenie niepoprawnej liczby wierszy i kolumny skutkuje utworzeniem macierzy 0x0 (niezainicjalizowanej)." << endl
		<< endl
		<< "Wprowadz liczbe wierszy: ";
	int w;
	cin >> w;
	cout
		<< "Wprowadz liczbe kolumn: ";
	int k;
	cin >> k;
	cout
		<< "Wprowadz domyslna wartosc: ";
	double wartosc;
	cin >> wartosc;

	string nazwa;
	cout
		<< "Wprowadz nazwe: ";
	cin >> nazwa;

	return Macierz(w, k, wartosc, nazwa);
}

static void wymien_macierze() {
	int rozmiar = macierze.n();
	for (int i = 0; i < rozmiar; i++) {
		cout << "[" << i << "]: " << macierze[i].nazwa;
		if (i < rozmiar - 1) {
			cout << ", ";
		}
	}
	cout << endl;
}

static void menu_macierzy() {
	int wybor;
	do {
		system("cls");
		cout
			<< "Menu macierzy:" << endl
			<< endl;
			wymien_macierze();
		cout << endl
			<< "0. Wyjdz" << endl
			<< endl
			<< "1. Wyswietl macierz." << endl
			<< "2. Dodaj macierz. " << endl
			<< "3. Usun macierz. " << endl
			<< endl
			<< "Wybor: ";
		cin >> wybor;

		switch (wybor) {
			case 1:
				wyswietl_macierze();
				break;
			case 2:
				dodaj_macierz();
				break;
			case 3:
				usun_macierz();
				break;
			default: break;
		}

	} while (wybor != 0);
}

static void wyswietl_macierze() {
	system("cls");
	int rozmiar = macierze.n();
	if (rozmiar == 0) {
		int ok;
		cout
			<< "Brak macierzy do wyswietlenia." << endl
			<< endl
			<< "Zatwierdz 1: ";
		cin >> ok;
	}
	else {
		int wybor;
		wymien_macierze();
		cout 
			<< endl;
		while(1){
			cout 
				<< "Wprowadz numer macierzy (-1: wyjscie, -2: czyszczenie): ";
			cin >> wybor;
			if (wybor == -1) {
				break;
			}
			if (wybor == -2) {
				system("cls");
				wymien_macierze();
				cout
					<< endl;
			}
			else if (wybor >= 0 and wybor < rozmiar) {
				cout
					<< macierze[wybor];
			}
			else {
				cout
					<< endl
					<< "Nieprawidlowy indeks." << endl
					<< endl;
			}
		};
	}
}

static void dodaj_macierz() {
	Macierz X(kreator_macierzy());
	
	int wybor = 2;
	do {
		system("cls");
		cout
			<< "Twoja macierz: "
			<< endl
			<< X
			<< endl
			<< "Co chcesz dalej zrobic?" << endl
			<< endl
			<< "0. Zakonczyc" << endl
			<< "1. Zmienic element" << endl
			<< "2. Anulowac kreacje" << endl
			<< endl
			<< "Wybor: ";
		cin >> wybor;

		switch (wybor) {
			case 1:
				int w, k;
				double wartosc;
				cout
					<< endl
					<< "Wprowadz wiersz: ";
				cin >> w;
				cout
					<< "Wprowadz kolumne: ";
				cin >> k;
				cout
					<< "Wprowadz wartosc: ";
				cin >> wartosc;

				X(w, k) = wartosc;
				break;
			default: break;
		}
	} while (wybor != 0 and wybor != 2);
	if (wybor == 0) {
		macierze.dorzuc(X);
	}
}

static void usun_macierz() {
	system("cls");
	if (macierze.n() == 0) {
		int ok;
		cout
			<< "Brak macierzy do wyswietlenia. " << endl
			<< endl
			<< "Zatwierdz 1: ";
		cin >> ok;
	}
	else {
		int wybor;
		while(1){
			int rozmiar = macierze.n();
			if (rozmiar == 0) {
				break;
			}
			wymien_macierze();
			cout
				<< endl
				<< "Wprowadz numer macierzy (-1: wyjscie): ";
			cin >> wybor;
			system("cls");
			if (wybor == -1) {
				break;
			}
			else if (wybor >= 0 and wybor < rozmiar) {
				macierze.usun(wybor);
				cout
					<< "Usunieto." << endl
					<< endl;
			}
			else {
				cout
					<< "Nieprawidlowy indeks macierzy." << endl
					<< endl;
			}
		};
	}
}

static void menu_funkcji(){
	int wybor;
	do {
		system("cls");
		cout
			<< "Menu funkcji operujacych na macierzach." << endl
			<< endl
			<< "0. Wyjscie" << endl
			<< endl
			<< "1. Eliminacja Gaussa-Croute'a." << endl
			<< "2. Metoda iteracji Jacobiego. " << endl
			<< "3. Metoda iteracji Gaussa-Siedla. " << endl
			<< endl
			<< "Wybor: ";
		cin >> wybor;
		
		switch (wybor) {
			case 1:
				wykonaj_eliminacje_gaussa_crouta();
				break;
			case 2:
				wykonaj_metode_jacobiego();
				break;
			case 3:
				wykonaj_metode_gaussa_siedla();
				break;
			default: break;
		}
	} while (wybor != 0);
}

static void wybierz_macierze_ukladu(int& i_A, int& i_b) {
	cout
		<< "UWAGA! Wybrane macierze musza spelniac odpowiednie zalozenia:" << endl
		<< endl
		<< "1. Macierz wspolczynnikow musi byc kwadratowa." << endl
		<< "2. Macierz wyrazow wolnych musi byc kolumnowa." << endl
		<< "3. Liczba kolumn macierzy wspolczynnikow musi byc rowna liczbie wierszy macierzy wyrazow wolnych." << endl
		<< endl;
	wymien_macierze();
	cout
		<< endl
		<< "Wybierz macierz wspolczynnikow: ";
	cin >> i_A;
	cout
		<< endl
		<< "Wybierz macierz wyrazow wolnych: ";
	cin >> i_b;
}

static void wykonaj_eliminacje_gaussa_crouta() {
	system("cls");
	int rozmiar = macierze.n();
	if (rozmiar == 0) {
		cout
			<< "Brak macierzy do pracy z algorytmem." << endl
			<< endl;
	}
	else {
		int i_A, i_b;
		wybierz_macierze_ukladu(i_A, i_b);
		Macierz x(eliminacja_gaussa_croute(macierze[i_A], macierze[i_b]));

		cout
			<< endl
			<< "Wynik GC: "
			<< x
			<< endl;
	}
	int ok;
	cout 
		<< "Zatwierdz 1: ";
		cin >> ok;
}

static void wykonaj_metode_jacobiego() {
	system("cls");
	int rozmiar = macierze.n();
	if (rozmiar == 0) {
		cout
			<< "Brak macierzy do pracy z algorytmem." << endl
			<< endl;
	}
	else {
		int i_A, i_b;
		wybierz_macierze_ukladu(i_A, i_b);
		Macierz x(metoda_jacobiego(macierze[i_A], macierze[i_b], 20));

		cout
			<< endl
			<< "Wynik J: "
			<< x
			<< endl;
	}
	int ok;
	cout
		<< "Zatwierdz 1: ";
	cin >> ok;
}

static void wykonaj_metode_gaussa_siedla() {
	system("cls");
	int rozmiar = macierze.n();
	if (rozmiar == 0) {
		cout
			<< "Brak macierzy do pracy z algorytmem." << endl
			<< endl;
	}
	else {
		int i_A, i_b;
		wybierz_macierze_ukladu(i_A, i_b);
		Macierz x(metoda_gaussa_siedla(macierze[i_A], macierze[i_b], 20));

		cout
			<< endl
			<< "Wynik GS: "
			<< x
			<< endl;
	}
	int ok;
	cout
		<< "Zatwierdz 1: ";
	cin >> ok;
}
