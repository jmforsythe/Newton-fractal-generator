#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "polynomial.hpp"


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

size_t Polynomial::get_degree() {
	return _degree;
}

std::string Polynomial::to_string() {
	std::stringstream ss;
	size_t i;
	for (i=0; i<=_degree; i++) {
		if (i == 0) ss << "(" << _coeff[i].to_string() << ")";
		else if (i == 1) ss << "+(" << _coeff[i].to_string() << ")X";
		else ss << "+(" << _coeff[i].to_string() << ")X^" << i;
	}
	return ss.str();
}

Complex Polynomial::evaluate(Complex z) {
	if (_degree == 0) return _coeff[0];
	std::vector<Complex> trunc_coeff = _coeff;
	trunc_coeff.erase(trunc_coeff.begin());
	Polynomial trunc_poly = Polynomial(trunc_coeff);
	return _coeff[0] + z*trunc_poly.evaluate(z);
}

Polynomial Polynomial::derivative() {
	std::vector<Complex> deriv_coeff;
	if (_degree == 0) {
		deriv_coeff = {Complex(0)};
	} else {
		deriv_coeff = _coeff;
		for (size_t i=0; i<=_degree; i++) {
			deriv_coeff[i] = deriv_coeff[i] * i;
		}
		deriv_coeff.erase(deriv_coeff.begin());
	}
	Polynomial deriv_poly = Polynomial(deriv_coeff);
	return deriv_poly;
}

std::ostream & operator<< (std::ostream & str, Polynomial & p) {
	str << p.to_string();
	return str;
}