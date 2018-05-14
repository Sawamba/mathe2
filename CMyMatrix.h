#pragma once
#include "CMyVektor.h"

using namespace std;

class CMyMatrix
{
private:
	int dimension_m;
	int dimension_n;
	//für vector m_row wird CMyVektor benutzt
	vector<CMyVektor> n_rows;
public:
	CMyMatrix();
	CMyMatrix(int m, int n);
	~CMyMatrix();

	int getDimension_m() { return dimension_m; }
	int getDimension_n() { return dimension_n; }
	string printWerte();

	CMyVektor &operator [](int n);
	CMyMatrix invers();
	CMyVektor operator*(CMyVektor x);
	
};

CMyMatrix jacobi(CMyVektor x, CMyVektor(*funktion)(CMyVektor x));
CMyVektor newton(CMyVektor x, CMyVektor(*funktion)(CMyVektor x));

