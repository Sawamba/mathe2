#include "CMyMatrix.h"
#include <iostream>

using namespace std;

CMyVektor f(CMyVektor x) {
	CMyVektor result(3);
	result[0] = x[0] * x[1] * exp(x[2]);
	result[1] = x[1] * x[2] * x[3];
	result[2] = x[3];
	return result;
}

CMyVektor g(CMyVektor x) {
	CMyVektor result(2);
	result[0] = (pow(x[0], 3) * pow(x[1], 3)) - 2 * x[1];
	result[1] = x[0] - 2;
	return result;
}

int main() {
	CMyMatrix mat(3, 4);
	CMyVektor x(4);
	x[0] = 1;
	x[1] = 2;
	x[2] = 0;
	x[3] = 3;

	CMyVektor result(2);
	CMyVektor vektor(2);
	vektor[0] = 1;
	vektor[1] = 1;

	mat = jacobi(x, f);

	for (int i = 0; i < mat.getDimension_m(); i++) {
		for (int j = 0; j < mat.getDimension_n(); j++) {
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
	cout << mat.printWerte();

	cout << endl;

	result = newton(vektor, g);
	//cout << result.printWerte();
	
	cout << endl;
	
	system("pause");
}