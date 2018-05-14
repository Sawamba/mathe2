#pragma once
#include <vector>
#include <string>

using namespace std;

class CMyVektor
{
private:
	int dimension;
	vector<double> werte;
public:
	CMyVektor();
	CMyVektor(int n);
	CMyVektor(CMyVektor const &orig);
	~CMyVektor();
	int const getDimension();
	void setWert(int stelle, double wert);
	double const getWert(int stelle);
	double const getLaenge();
	string printWerte();
	
	double &operator [](int stelle);
	CMyVektor operator+(CMyVektor b);
	CMyVektor operator*(double lambda);
};

CMyVektor gradient(CMyVektor x, double(*funktion)(CMyVektor x));
CMyVektor gradientenverfahren(CMyVektor x, double(*funktion)(CMyVektor x), double lambda = 1.0);
