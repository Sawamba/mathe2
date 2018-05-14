#include "CMyVektor.h"
#include <iostream>



CMyVektor::CMyVektor()
{
	dimension = 1;
	werte.resize(dimension);
}

CMyVektor::CMyVektor(int n)
{
	dimension = n;
	werte.resize(dimension);
}

CMyVektor::CMyVektor(const CMyVektor &orig) {
	dimension = orig.dimension;
	werte.resize(dimension);
	for (int i = 0; i < dimension; i++)
		werte.at(i) = orig.werte.at(i);
}



CMyVektor::~CMyVektor()
{
}

int const CMyVektor::getDimension() {
	return dimension;
}

void CMyVektor::setWert(int stelle, double wert) {
	werte.at(stelle) = wert;
}

double const CMyVektor::getWert(int stelle) {
	return werte.at(stelle);
}

double const CMyVektor::getLaenge() {
	double laenge = 0;
	for (int i = 0; i < dimension; i++)
		laenge += pow(werte.at(i), 2);
	laenge = sqrt(laenge);
	return laenge;
}

CMyVektor gradient(CMyVektor x, double (*funktion)(CMyVektor x)) {
	double h = pow(10, -8);
	CMyVektor tmp = x;
	CMyVektor gradient(x.getDimension());
	for (int i = 0; i < x.getDimension(); i++) {
		tmp[i] += h;
		gradient[i] = (funktion(tmp) - funktion(x)) / h;
		tmp[i] = x[i];
	}
	return gradient;
}

CMyVektor gradientenverfahren(CMyVektor x, double(*funktion)(CMyVektor x), double lambda) {
	CMyVektor x_neu(x.getDimension());
	CMyVektor grad = gradient(x, funktion);
	
	for (int i = 0; i < 50 && grad.getLaenge() >= pow(10, -5); i++) {
		x_neu = x + (gradient(x, funktion) * lambda);
		if (funktion(x_neu) > funktion(x)) {
			CMyVektor x_test(x.getDimension());
			x_test = x + (gradient(x, funktion) * 2 * lambda);
			if (funktion(x_test) > funktion(x_neu)) {
				x = x_test;
				lambda *= 2;
			}
			else
				x = x_neu;
		}
		else {
			while (funktion(x_neu) <= funktion(x)) {
				lambda /= 2;
				x_neu = x + (gradient(x, funktion) * lambda);
			}
			x = x_neu;
		}
		grad = gradient(x, funktion);
	}
	return x;
}

string CMyVektor::printWerte() {
	string ausgabe;
	ausgabe = "( ";
	for (int i = 0; i < dimension - 1; i++) {
		ausgabe += to_string(werte.at(i));
		ausgabe += ", ";
	}
	ausgabe += to_string(werte.at(dimension - 1));
	ausgabe += " )";
	return ausgabe;
}

double& CMyVektor::operator [](int stelle) {
	if (stelle >= dimension) std::cout << "Error: Out of bounds\n";
	else return werte.at(stelle);
}

CMyVektor CMyVektor::operator+(CMyVektor b) {
	if (this->dimension != b.dimension) std::cout << "Error: Addition impossible!\n";
	else {
		CMyVektor vektor(dimension);
		for (int i = 0; i < dimension; i++)
			vektor.werte.at(i) = this->werte.at(i) + b.werte.at(i);
		return vektor;
	}
}

CMyVektor CMyVektor::operator*(double lambda) {
	CMyVektor vektor(dimension);
	for (int i = 0; i < dimension; i++)
		vektor.werte.at(i) = this->werte.at(i) * lambda;
	return vektor;
}
