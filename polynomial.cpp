#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "complex.h"
#include "polynomial.h"


Polynomial::Polynomial(std::vector<Complex> coeff) {
	if (coeff.size() > 0) {
		_coeff = coeff;
		while (!_coeff.empty() && _coeff.back() == Complex(0,0) && _coeff.size() >= 1) {
			_coeff.pop_back();
		}
		if (_coeff.size() > 0) {
			_degree = _coeff.size() - 1;
		} else {
			_degree = 0;
		}
	} else {
		_coeff = {Complex()};
		_degree = 0;
	}
}
Polynomial::Polynomial() {
	_coeff = {Complex()};
	_degree = 0;
}

int Polynomial::getDegree() {
	return _degree;
}

std::string Polynomial::toString() {
	std::stringstream ss;
	int i;
	for (i=0; i<=_degree; i++) {
		if (i == 0) ss << "(" << _coeff[i].toString() << ")";
		else if (i == 1) ss << "+(" << _coeff[i].toString() << ")X";
		else ss << "+(" << _coeff[i].toString() << ")X^" << i;
	}
	return ss.str();
}

Complex Polynomial::evaluate(Complex z) {
	if (_degree == 0) return _coeff[0];
	std::vector<Complex> truncCoeff = _coeff;
	truncCoeff.erase(truncCoeff.begin());
	Polynomial truncPoly = Polynomial(truncCoeff);
	return _coeff[0] + z*truncPoly.evaluate(z);
}

Polynomial Polynomial::derivative() {
	std::vector<Complex> derivCoeff;
	if (_degree == 0) {
		derivCoeff = {Complex(0)};
	} else {
		derivCoeff = _coeff;
		int i;
		for (i=0; i<=_degree; i++) {
			derivCoeff[i] = derivCoeff[i] * i;
		}
		derivCoeff.erase(derivCoeff.begin());
	}
	Polynomial derivPoly = Polynomial(derivCoeff);
	return derivPoly;
}

std::ostream & operator<< (std::ostream & str, Polynomial & p) {
	str << p.toString();
	return str;
}

/*
int main() {
	std::vector<Complex> coeffs = {Complex(1),Complex(),Complex(1),Complex(1)};
	Polynomial p(coeffs);
	std::cout << p << std::endl;
	std::cout << p.evaluate(Complex(1)) << std::endl;
	Polynomial q = p.derivative();
	std::cout << q << std::endl;
	return 0;
}
*/