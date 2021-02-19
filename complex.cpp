#include <string>
#include <sstream>
#include <math.h>
#include <iostream>
#include <cassert>
#include "Complex.h"

Complex::Complex(double x, double y) {
	_x = x;
	_y = y;
}
Complex::Complex(double x) {
	_x = x;
	_y = 0;
}
Complex::Complex() {
	_x = 0;
	_y = 0;
}

double Complex::getReal() const {
	return _x;
}
double Complex::getImag() const {
	return _y;
}

std::string Complex::toString() const {
	std::stringstream s;
	s << _x;
	if (_y >= 0) s << "+" << _y;
	else s << "-" << -_y;
	s << "i";
	return s.str();
}

double Complex::abs2() const {
	return (_x * _x) + (_y * _y);
}

Complex Complex::conjugate() const {
	return Complex(_x, -_y); 
}

Complex Complex::reciprocal() const {
	return conjugate()/abs2();
}

Complex operator+(const Complex &a, const Complex &b) {
	double ar,br,ai,bi;
	ar = a.getReal();
	br = b.getReal();
	ai = a.getImag();
	bi = b.getImag();
	return Complex(ar + br, ai + bi);
}

Complex operator-(const Complex &a, const Complex &b) {
	double ar,br,ai,bi;
	ar = a.getReal();
	br = b.getReal();
	ai = a.getImag();
	bi = b.getImag();
	return Complex(ar - br, ai - bi);
}

Complex operator*(const Complex &a, const Complex &b) {
	double ar,br,ai,bi;
	ar = a.getReal();
	br = b.getReal();
	ai = a.getImag();
	bi = b.getImag();
	return Complex((ar*br) - (ai*bi), (ai*br) + (ar*bi));
}

Complex operator*(const Complex &a, const double &b) {
	double ar,ai;
	ar = a.getReal();
	ai = a.getImag();
	return Complex(ar*b, ai*b);
}

Complex operator*(const double &a, const Complex &b) {
	return b*a;
}

Complex operator/(const Complex &a, const Complex &b) {
	return a*b.reciprocal();
}

Complex operator/(const Complex &a, const double &b) {
	return a*(1.0/b);
}

Complex operator/(const double &a, const Complex &b) {
	return b.reciprocal()*a;
}

bool operator==(const Complex &a, const Complex &b) {
	return (a.getReal() == b.getReal() && a.getImag() == b.getImag());
}

std::ostream & operator<< (std::ostream & str, const Complex & z) {
	str << z.toString();
	return str;
}

/*
int main() {
	Complex x(1.0, 2.0);
	assert(x.toString() == "1+2i");
	Complex y = x.conjugate();
	assert(y == Complex(1.0, -2));
	double m = x.abs2();
	assert(m == (x*y).getReal());
	return 0;
}*/