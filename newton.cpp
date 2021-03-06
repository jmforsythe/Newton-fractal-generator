#include <vector>
#include <iostream>

#include "newton.hpp"
#include "polynomial.hpp"
#include "complex.hpp"

Newton::Newton() {
	std::vector<Complex> coeffs = {Complex()};
	_f = Polynomial(coeffs);
	_fp = _f.derivative();
	_max_iter = 4000;
}

Newton::Newton(Polynomial p) {
	_f = p;
	_fp = _f.derivative();
	_max_iter = 4000;
}

Newton::Newton(Polynomial p, int max_iter) {
	_f = p;
	_fp = _f.derivative();
	_max_iter = max_iter;
}

int Newton::get_error() {
	return _err;
}

size_t Newton::get_num_iterations() {
	return _num_iterations;
}

Complex Newton::get_root() {
	return _root;
}

Polynomial Newton::get_f() {
	return _f;
}

Polynomial Newton::get_fp() {
	return _fp;
}

void Newton::iterate(Complex z0) {
	_num_iterations = 0;
	Complex root = z0;
	int i;
	for (i=0; i<_max_iter; i++) {
		Complex fz = _f.evaluate(root);
		if (fz.abs2() < TOL2) {
			_root = root;
			_num_iterations = i;
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
	if (i >= _max_iter) _err = -2;
}