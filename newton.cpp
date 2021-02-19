#include <vector>
#include <iostream>

#include "newton.hpp"
#include "polynomial.hpp"
#include "complex.hpp"

Newton::Newton() {
	std::vector<Complex> coeffs = {Complex()};
	_f = Polynomial(coeffs);
	_fp = _f.derivative();
}

Newton::Newton(Polynomial p) {
	_f = p;
	_fp = _f.derivative();
}

int Newton::getError() {
	return _err;
}

int Newton::getNumIterations() {
	return _numIterations;
}

Complex Newton::getRoot() {
	return _root;
}

Polynomial Newton::getF() {
	return _f;
}

Polynomial Newton::getFp() {
	return _fp;
}

void Newton::iterate(Complex z0) {
	_numIterations = 0;
	Complex root = z0;
	int i;
	for (i=0; i<MAXITER; i++) {
		Complex fz = _f.evaluate(root);
		if (fz.abs2() < TOL2) {
			_root = root;
			_numIterations = i;
			_err = 0;
			break;
		}
		Complex fpz = _fp.evaluate(root);
		if (fpz.abs2() <= TOL2) {
			_err = -1;
			break;
		}
		root = root - (fz/fpz);
	}
	if (i >= MAXITER) _err = -2;
}

/*int main() {
	std::vector<Complex> coeff = {Complex (-1), Complex(), Complex(), Complex(1)};
	Polynomial p = Polynomial(coeff);
	Newton n = Newton(p);
	n.iterate(Complex(1,1));
	std::cout << n.getRoot() << std::endl;
	return 0;
}*/