#include <iostream>
#include "macierz_interfejs.h"
#include "dynamiczne_macierze.h"
#include "macierz_globalne.h"
#include "macierz.h"

using namespace std;

int main() {

	Macierz A(3, 3, 0, "A"), b(3, 1, 0, "b");

	A(1, 1) = 10.0;
	A(1, 2) = 1.0;
	A(1, 3) = 2.0;

	A(2, 1) = 2.0;
	A(2, 2) = -10.0;
	A(2, 3) = 2.0;

	A(3, 1) = 4.0;
	A(3, 2) = 1.0;
	A(3, 3) = 10.0;


	b(1, 1) = 1.3;
	b(2, 1) = -0.6;
	b(3, 1) = 1.5;

	macierze.dorzuc(A);
	macierze.dorzuc(b);
	macierze.dorzuc(3, 3, -1, "X");
	macierze.dorzuc(3, 3, 0, "Y");
	macierze.dorzuc(3, 3, 1, "Z");
	menu_glowne();
}