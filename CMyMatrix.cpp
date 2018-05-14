#include "CMyMatrix.h"
#include <iostream>


CMyMatrix::CMyMatrix()
{
	dimension_m = 1;
	dimension_n = 1;
	n_rows.resize(dimension_m);
	for (int i = 0; i < dimension_m; i++) {
		CMyVektor vek(dimension_n);
		n_rows.at(i) = vek;
	}
}

CMyMatrix::CMyMatrix(int m, int n) {
	dimension_m = m;
	dimension_n = n;
	n_rows.resize(dimension_m);
	for (int i = 0; i < dimension_m; i++) {
		CMyVektor vek(dimension_n);
		n_rows.at(i) = vek;
	}
}


CMyMatrix::~CMyMatrix()
{
}

string CMyMatrix::printWerte() {
	string werte;
	CMyMatrix mat = *this;
	werte += "(";
	for (int i = 0; i < dimension_m; i++) {
		werte += "{";
		for (int j = 0; j < dimension_n; j++) {
			werte += to_string(mat[i][j]);
			werte += ", ";
		}
		werte.erase(werte.size() - 2, 2);
		werte += "}, ";
	}
	werte.erase(werte.size() - 2, 2);
	werte += ")";
	return werte;
}

CMyVektor &CMyMatrix::operator[](int m)
{
	if (m >= dimension_m) std::cout << "Error: Out of bounds\n";
	else return n_rows.at(m);
}

CMyMatrix CMyMatrix::invers() {
	CMyMatrix mat = *this;
	if (dimension_m == 2 && dimension_n == 2) {
		if (mat[0][0] * mat[1][1] != mat[1][0] * mat[0][1]) { // Det != 0
			double invDet = 1 / ((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
			double zwischenspeicher = mat[0][0];
			mat[0][0] = invDet * mat[1][1];
			mat[0][1] *= (-1) * invDet;
			mat[1][0] *= (-1) * invDet;
			mat[1][1] = invDet * zwischenspeicher;
			return mat;
		}
		else
			cout << "Fehler: Determinante == 0.";
	}
	else
		cout << "Fehler: Matrix muss Dimensionen 2x2 haben.";
}

CMyVektor CMyMatrix::operator*(CMyVektor x) {
	CMyMatrix mat = *this;
	CMyVektor vek(dimension_m);
	if (dimension_n != x.getDimension())
		cout << "Fehler: Inkompatible Dimensionen.";
	else {
		for (int i = 0; i < dimension_m; i++) {
			double sum = 0.0;
			for (int j = 0; j < dimension_n; j++) {
				sum += mat[i][j] * x[j];
			}
			vek[i] = sum;
		}
		return vek;
	}
}

CMyMatrix jacobi(CMyVektor x, CMyVektor(*funktion)(CMyVektor x)) {
	CMyMatrix jmat(funktion(x).getDimension(), x.getDimension());
	CMyVektor tmp = x;
	double const h = pow(10, -4);
	for (int i = 0; i < funktion(x).getDimension(); i++) {
		CMyVektor gradient(x.getDimension());
		for (int j = 0; j < x.getDimension(); j++) {
			tmp[j] += h;
			gradient[j] = (funktion(tmp)[i] - funktion(x)[i] ) / h;
			tmp[j] = x[j];
		}
		jmat[i] = gradient;
	}
	return jmat;
}

CMyVektor newton(CMyVektor x, CMyVektor(*funktion)(CMyVektor x)) {
	CMyVektor x_neu = x;
	if (x.getDimension() != 2) {
		cout << "Fehler: Dimension muss 2 sein.";
		return x_neu;
	}
	
	int zaehler = 0;
	
	while (funktion(x_neu).getLaenge() >= pow(10, -5) && zaehler < 50) {
		CMyVektor dif(2);
		dif = jacobi(x_neu, funktion).invers() * (funktion(x_neu) * (-1));

		cout << "Schritt " << zaehler << ":\n\t"
			<< "x = " << x_neu.printWerte() << "\n\t"
			<< "f(x) = " << funktion(x_neu).printWerte() << "\n\t"
			<< "f'(x) = " << jacobi(x_neu, funktion).printWerte() << "\n\t"
			<< "f'(x)^(-1) = " << jacobi(x_neu, funktion).invers().printWerte() << "\n\t"
			<< "dx = " << dif.printWerte() << "\n\t"
			<< "||f(x)|| = " << funktion(x_neu).getLaenge() << "\n";
		
		x_neu = x_neu + dif;
		zaehler++;
	}
	if (zaehler == 50) {
		cout << "Ende wegen Schritt = 50 bei\n\t"
			<< "x = " << x_neu.printWerte() << "\n\t"
			<< "f(x) = " << funktion(x_neu).printWerte() << "\n\t"
			<< "||f(x)|| = " << funktion(x_neu).getLaenge() << "\n";
	}
	else {
		cout << "Ende wegen ||f(x)||<1e-5 bei\n\t"
			<< "x = " << x_neu.printWerte() << "\n\t"
			<< "f(x) = " << funktion(x_neu).printWerte() << "\n\t"
			<< "||f(x)|| = " << funktion(x_neu).getLaenge() << "\n";
	}
	return x_neu;
}
