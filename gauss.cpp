#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <iomanip>

using namespace std;

void writeArray(double** tab, unsigned int size, unsigned int m) {
	for (int i = 0; i < size; i++) {
		cout << endl;
		for (int j = 0; j < m; j++) {
			cout << tab[i][j] << " ";
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	cout << endl;
}

void add(double** tab, int a, int b, double n, unsigned int m) {
	for (int i = 0; i < m; i++) {
		tab[a][i] += n * tab[b][i];
	}
}

void multiply(double** tab, int a, double n, unsigned int m) {
	for (int i = 0; i < m; i++) {
		tab[a][i] *= n;
	}
}

void swap(double** tab, int a, int b) {
	if (a == b) {
		return;
	}
	double* temp = tab[a];
	tab[a] = tab[b];
	tab[b] = temp;
}

void step(double** tab, int n, unsigned int size, unsigned int m) {
	int i;
	for (i = n; i < size && tab[i][n] == 0; i++) {
		;
	}
	if (i == size) {
		return;
	}
	swap(tab, n, i);
	multiply(tab, n, 1 / tab[n][n], m);
	for (i = 0; i < size; i++) {
		if (i != n && tab[i][n] != 0) {
			add(tab, i, n, -tab[i][n], m);
		}
	}
}

int main() {
	setlocale(LC_ALL, "");
	unsigned int tabSize;
	unsigned int m;
	double x;
	bool choose = true;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << "Type amount of linear equations (Ax1+Bx2+...+CxN=D): " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cin >> tabSize;
	if (tabSize < 1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cout << "Impossible to solve!" << endl;
		return 0;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << endl << "Type amount of parameters: " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cin >> m;
	if (m < 2) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cout << "Impossible to solve!" << endl;
		return 0;
	}
	if (tabSize >= m) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cout << "Impossible to solve!" << endl;
		return 0;
	}
	double** tab = new double* [tabSize];
	for (int i = 0; i < tabSize; i++) {
		tab[i] = new double[m];
		cout << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		std::cout << "Type parameters ";
		cout << i + 1;
		cout << ". of linear equation: " << endl;
		for (int j = 0; j < m; j++) {
			if (j < m - 1) {
				cout << "x" << j + 1 << ": ";
			}
			else {
				cout << "D: ";
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cin >> x;
			tab[i][j] = x;
		}
	}
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	//writeArray(tab, tabSize, m);
	for (int i = 0; i < tabSize; i++) {
		step(tab, i, tabSize, m);
	}
	//writeArray(tab, tabSize, m);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << endl << "Solution: " << endl;
	for (int i = 0; i < tabSize; i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		std::cout << "x";
		cout << i + 1;
		cout << ": ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << tab[i][m-1] << endl;
	}
	return 0;
}
